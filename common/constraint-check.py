"""
constraint-check.py
(c) 2021-23 Christopher A. Bohn

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    https://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""

import itertools
import json
import os
import sys
from numbers import Number
from typing import Dict, Iterable, IO, List, Optional, Tuple, Union

interesting_code_blocks = frozenset({'do', 'while', 'for', 'switch'})       # TODO: parameterize
uninteresting_code_block_keywords = frozenset({'if', 'else', 'return'})     # TODO: parameterize


def is_real_delimiter(delimiter: str, line: str) -> bool:
    is_real = True
    before, during, after = line.strip().partition(delimiter)
    while len(after) > 0:
        is_real = True
        if len(before) > 0:
            # is it part of a string?
            if (before.count('"') % 2 == 1) and (after.count('"') % 2 == 1):
                is_real = False
            # is it a literal character?
            if (before[-1] == '\'') and (after[0] == '\''):
                is_real = False
            # even if that occurrence wasn't a real delimiter, is there another occurrence?
            if not is_real:
                before, during, after = after.strip().partition(delimiter)
            else:
                after = ''
        else:
            after = ''
    return is_real


def keyword_is_present(keyword: str, line: str, code_block_start: str, code_block_end: str) -> bool:
    found_keyword = False
    if keyword in line:
        before, during, after = line.strip().partition(keyword)
        # determine if this is truly a keyword and not part of an identifier
        if (before == '' or before[-1] in {' ', '\t', ')', code_block_end}) and \
                (after == '' or after[0] in {' ', '\t', '(', ';', code_block_start}):
            found_keyword = True
        # determine if it is part of a string
        #           okay for C, but won't work for multiline strings
        #           will also fail if there's an escaped double-quote in a string: "foo\"bar"
        if found_keyword:
            if (before.count('"') % 2 == 1) and (after.count('"') % 2 == 1):
                found_keyword = False
    return found_keyword


def remove_comments(line: str, is_inside_comment_block: bool, block_comment_start: str,
                    block_comment_end: str, line_comment: str) -> Tuple[str, bool]:
    if is_inside_comment_block:
        if block_comment_end in line:
            _, _, line = line.partition(block_comment_end)
            is_inside_comment_block = False
        else:
            line = ''
    while block_comment_start in line:
        line, _, line_remainder = line.partition(block_comment_start)
        is_inside_comment_block = True
        if block_comment_end in line_remainder:
            _, _, line_remainder = line_remainder.partition(block_comment_end)
            is_inside_comment_block = False
            line = f'{line} {line_remainder}'
    line = line.split(line_comment)[0]
    return line, is_inside_comment_block


def track_code_blocks(code_block_stack: List[str], line: str, code_block_start: str, code_block_end: str) -> List[str]:
    # are we starting or ending a code block?
    brace_has_been_processed: bool = False
    possible_code_block: Optional[str] = None
    for keyword in interesting_code_blocks:
        if keyword in line:
            before, during, after = line.strip().partition(keyword)
            # let's assume that the code block's keyword will always be at the start of a line
            # (there is legal code in which it isn't, such as `if (...) do {`, but let's assume away weirdness
            if before == '' and (after == '' or after[0] in {' ', '\t', '(', code_block_start}):
                possible_code_block = keyword
                if code_block_start in after:
                    code_block_stack.append(keyword)
                    possible_code_block = None
                    brace_has_been_processed = True
    if code_block_start in line and not brace_has_been_processed:
        if is_real_delimiter(code_block_start, line):
            if possible_code_block is not None:
                code_block_stack.append(possible_code_block)
                # possible_code_block = None
            else:
                code_block_stack.append('OTHER')
    if code_block_end in line:
        if is_real_delimiter(code_block_end, line):
            code_block_stack.pop()
    # # a few resets
    # brace_has_been_processed = False
    # for keyword in uninteresting_code_block_keywords:
    #     if keyword_is_present(keyword, line, code_block_start, code_block_end):
    #         possible_code_block = None
    return code_block_stack


# noinspection PyUnusedLocal
def hunt_for_violations(target_file: IO,
                        comment_delimiters: Dict[str, Union[str, List[str]]],
                        code_block_delimiters: List[str],
                        disallowed_calls: Iterable[str],                    # TODO: handle disallowed function calls
                        disallowed_keywords: Iterable[str],
                        limited_loop_terminations: Dict[int, Iterable[str]],
                        limited_characters: Dict[int, Iterable[str]]) -> List[str]:
    violations: List[str] = []
    is_inside_comment_block: bool = False
    code_block_stack: List[str] = []
    line_number = 0

    line_comment = comment_delimiters['inlineComment']
    block_comment_start, block_comment_end = comment_delimiters['blockComment']
    code_block_start, code_block_end = code_block_delimiters

    # TODO: handle limited but non-prohibited loop terminations (e.g., MISRA allows 1 `break` per loop)
    disallowed_loop_terminations = limited_loop_terminations[0]
    limited_character_occurrences: Dict[str, List[str]] = \
        {c: [] for c in itertools.chain.from_iterable(limited_characters.values())}

    for line in target_file:
        line_number += 1
        # first some bookkeeping
        line, is_inside_comment_block = remove_comments(line, is_inside_comment_block,
                                                        block_comment_start, block_comment_end, line_comment)
        code_block_stack = track_code_blocks(code_block_stack, line, code_block_start, code_block_end)
        # now let's look for violations
        for character in limited_character_occurrences.keys():
            number_of_occurrences: int = line.count(character)
            while number_of_occurrences > 0:
                limited_character_occurrences[character].append(f'line {line_number}: {line}')
                number_of_occurrences -= 1
        for keyword in disallowed_keywords:
            if keyword_is_present(keyword, line, code_block_start, code_block_end):
                violations.append(f'`{keyword}` in {target_file.name} on line {line_number}: {line}')
        for keyword in disallowed_loop_terminations:
            if keyword_is_present(keyword, line, code_block_start, code_block_end):
                if keyword == 'break' and code_block_stack[-1] == 'switch':
                    pass
                else:
                    block = None
                    for code_block in code_block_stack:
                        if code_block not in {'switch', 'OTHER'}:
                            block = code_block
                    if block is not None:
                        violations.append(f'`{keyword}` used to terminate `{block}` loop'
                                          f' in {target_file.name} on line {line_number}: {line}')
    for character in limited_character_occurrences:
        allowable_occurrences = list(filter(lambda i: character in limited_characters[i], limited_characters))[0]
        actual_occurrences = len(limited_character_occurrences[character])
        if actual_occurrences > allowable_occurrences:
            violations.append(f'\'{character}\' occurs '
                              f'{f"{actual_occurrences} times " if actual_occurrences > 1 else ""}'
                              f'in {target_file.name}')
            # we used a list to track the occurrences so that we could count them, but now
            # we'll convert that into a set so that we don't print a line with multiple occurrences multiple times
            violations.extend({f'\t{detail}' for detail in limited_character_occurrences[character]})
    return [v.replace(os.linesep, '') for v in violations]


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Usage: python constraint-check.py rulesfile.json')
        print('    where rulesfile.json is the name of the json file with this assignment\'s prohibitions')
        sys.exit(-1)
    else:
        report: List[str] = []
        violation_count: int = 0
        with open(sys.argv[1], 'r') as rules_file:
            rules: Dict[str, Union[str, Number, List, Dict]] = json.load(rules_file)
            for filename in rules['targetFiles']:
                with open(filename, 'r') as source_code_file:
                    violations_in_file = hunt_for_violations(
                        target_file=source_code_file,
                        comment_delimiters=rules['commentDelimiters'],
                        code_block_delimiters=rules['codeBlockDelimiters'],
                        disallowed_calls=rules['disallowedCalls'],
                        disallowed_keywords=rules['disallowedKeywords'],
                        limited_loop_terminations={int(limit): set(keywords) for limit, keywords in
                                                   rules['limitedLoopTerminations'].items()},
                        limited_characters={int(limit): set(characters) for limit, characters in
                                            rules['limitedCharacters'].items()}
                    )
                    if len(violations_in_file) == 0:
                        report.append(f'constraint-check.py found no violations'
                                      f' specified by {sys.argv[1]} in {filename}.')
                    else:
                        violation_count += len(violations_in_file)
                        report.extend(violations_in_file)
        for violation in report:
            print(violation)
        sys.exit(0 if violation_count == 0 else 1)
