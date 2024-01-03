import functools
import inflect
import json
import os
import shutil
import sys
import urllib.request
import urllib.error
from typing import Dict, List, Set, Optional, Union


def validate_labs_existence(semester: List[Dict], labs: Dict) -> bool:
    semester_labs: Set[str] = {lab['lab'] for lab in semester}
    missing_labs = semester_labs - labs.keys()
    if missing_labs:
        print(f'Missing data for: {missing_labs}', file=sys.stderr)
        validated = False
    else:
        lab_locations: List[str] = [labs[lab['lab']]['location'] for lab in semester]
        existences: List[bool] = [os.path.exists(location) for location in lab_locations]
        validated = functools.reduce(lambda a, b: a & b, existences)
        if not validated:
            unknown_locations = [lab_locations[index] for index, value in enumerate(existences) if not value]
            print(f'Unknown file path(s): {unknown_locations}', file=sys.stderr)
    return validated


def validate_lab_specific_keys(lab: Dict, storyline: Dict) -> bool:
    if storyline is None:
        storyline = {}
    else:
        storyline = storyline[lab['lab']]
    validated: bool = True
    for key in lab['lab-specific keys']:
        if key not in lab and key not in storyline:
            print(f'Lab specific key "{key}" is not present for KeyboardLab', file=sys.stderr)
            validated = False
        elif key in lab and not isinstance(lab[key], str):
            print(f'KeyboardLab value for key "{key}" is not a string: {lab[key]}', file=sys.stderr)
            validated = False
        elif key in storyline and not isinstance(storyline[key], str):
            print(f'KeyboardLab value for key "{key}" is not a string: {storyline}', file=sys.stderr)
            validated = False
    return validated


def generate_keyboardlab_latex_macros(lab: Dict, storyline: Dict) -> str:
    # TODO: validate appropriateness of missing key
    if validate_lab_specific_keys(lab, storyline):
        missing_key: str = lab['first missing key'].upper()
        message: str = lab['desired email']
    else:
        missing_key: str = 'C'
        message: str = 'ERROR: KeyboardLab did not pass validation\n'
    lowercase_key: str = missing_key.lower()
    tab_character = '\t'
    latex_tab_replacement = '\\tab '
    c_tab_replacement = '\\textbackslash t'
    newline_character = '\n'
    latex_newline_replacement = '\\nl '
    c_newline_replacement = '\\textbackslash n'
    email: str = ''
    for line in message.split('\n'):
        email += f'\\texttt{{{line.replace(tab_character, latex_tab_replacement)}{latex_newline_replacement}}} \\\\'
    c_function = ''
    for line in message.split('\n'):
        c_function += ('\\texttt{{\\phantom{{xxxxxxxxxxx}}"'
                       f'{line.replace(tab_character, c_tab_replacement)}{c_newline_replacement}'
                       '"}} \\\\\n')
    adhesive: str = storyline[lab['lab']]['adhesive']
    return (f'\\newcommand{{\\missingKey}}{{{missing_key}}}\n'
            f'\\newcommand{{\\lowercaseKey}}{{{lowercase_key}}}\n'
            f'\\newcommand{{\\email}}{{{email}}}\n'
            f'\\newcommand{{\\cString}}{{{c_function}}}\n'
            f'\\newcommand{{\\adhesive}}{{{adhesive}}}\n')


def generate_keyboardlab_starter_code(lab: Dict, storyline: Dict) -> None:
    # TODO: parameterize problems 2 & 3
    if validate_lab_specific_keys(lab, storyline):
        message: str = lab['desired email']
    else:
        message: str = 'ERROR: KeyboardLab did not pass validation\n'
    with open(f'{lab["location"]}/starter-code/problem1oracle.txt', mode='w') as output_file:
        output_file.write(message + '\n')


def prep_latex(lab: Dict, lab_number: int, course_term: str, storyline: Dict,
               previous_lab: Optional[str], next_lab: Optional[str], tex: str):
    short_labname = lab['lab']
    filename_core: str = short_labname.lower()
    # describe the course
    tex += f'\\newcommand{{\\institutename}}{{{lab["course information"]["institute"]}}}\n'
    tex += f'\\newcommand{{\\instructorname}}{{{lab["course information"]["instructor"]}}}\n'
    tex += f'\\newcommand{{\\coursenumber}}{{{lab["course information"]["course number"]}}}\n'
    tex += f'\\newcommand{{\\cstwo}}{{{lab["course information"]["cs2 course"]}}}\n'
    tex += f'\\newcommand{{\\courseterm}}{{{course_term}}}\n'
    # describe the assignment
    tex += f'\\newcommand{{\\labnumber}}{{{lab_number}}}\n'
    tex += f'\\newcommand{{\\labname}}{{{lab["lab name"]}}}\n'
    tex += f'\\newcommand{{\\shortlabname}}{{{short_labname}}}\n'
    tex += f'\\newcommand{{\\duedate}}{{{lab["due"]}}}\n'
    # file flow
    tex += f'\\newcommand{{\\filesource}}{{{lab["file flow"]["source"]}}}\n'
    tex += f'\\newcommand{{\\filesubmission}}{{{lab["file flow"]["submission"]}}}\n'
    tex += f'\\newcommand{{\\runtimeenvironment}}{{{lab["file flow"]["runtime environment"]}}}\n'
    tex += f'\\newcommand{{\\startercode}}{{{filename_core}.zip or {filename_core}.tar}}\n'
    tex += f'\\newcommand{{\\requiredfiles}}{{{lab["required files"]}}}\n'
    # policies
    tex += f'\\newcommand{{\\collaborationrules}}{{{lab["policies"]["collaboration"][0]}}}\n'
    # TODO: handle additional collaboration elements
    tex += f'\\newcommand{{\\policyforcodethatdoesnotcompile}}{{{lab["policies"]["grading"]["uncompilable"]}}}\n'
    tex += f'\\newcommand{{\\latepolicy}}{{{lab["policies"]["grading"]["late"]}}}\n'
    tex += \
        f'\\newcommand{{\\softwareengineeringfrontmatter}}{{{lab["policies"]["software engineering"][0]["policy"]}}}\n'
    tex += \
        f'\\newcommand{{\\softwareengineeringpenalties}}{{{lab["policies"]["software engineering"][0]["penalty"]}}}\n'
    # TODO: handle additional SE elements
    # storyline
    todays_episode = storyline[short_labname]
    scenario_introduction: str = f'{storyline["story introduction"]}\n{todays_episode["introduction"]}' \
        if lab_number == 1 else f'{todays_episode["introduction"]}'
    if previous_lab is not None:
        scenario_introduction = storyline[previous_lab]['callback'] + scenario_introduction
    tex += f'\\newcommand{{\\scenariointroduction}}{{{scenario_introduction}}}\n'
    tex += f'\\newcommand{{\\scenariowrapup}}{{{todays_episode["wrapup"]}}}\n'
    if todays_episode['progress'] is not None:
        for index, transition in enumerate(todays_episode['progress']):
            # number = inflect.engine.number_to_words(0, zero='zero', one='one')
            number = ['zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine'][index]
            tex += f'\\newcommand{{\\transition{number}}}{{{transition}}}\n'
    # TODO: handle storyline conclusion
    # TODO: handle teasers
    if 'lab-specific keys' in lab and lab['lab-specific keys'] is not None:
        tex += globals()[f'generate_{filename_core}_latex_macros'](lab, storyline)
    # output the LaTeX customization
    with open(f'{lab["location"]}/assignment/assignment-definitions.tex', mode='w') as output_file:
        output_file.write(tex)
    # copy any necessary images
    images: List[Union[str, Dict[str, str]]] = []
    if 'introduction image' in storyline and lab_number == 1:
        images.append(storyline['introduction image'])
    for key in {'teaser image', 'introduction image', 'wrapup image', 'callback image'}:
        if key in todays_episode:
            images.append(todays_episode[key])
    # TODO: save teaser & callback images to correct directories
    for image_description in images:
        match image_description:
            case str():
                if os.path.isfile(f'customization/storylines/{storyline["introduction image"]}'):
                    shutil.copy(src=f'customization/storylines/{storyline["introduction image"]}',
                                dst=f'{lab["location"]}/assignment/', follow_symlinks=True)
                else:
                    print('No such file for introduction image:'
                          f' customization/storylines/{storyline["introduction image"]}')
            case dict():
                if 'link' in image_description and image_description['link'] is not None:
                    try:
                        with urllib.request.urlopen(image_description["link"]) as image_url:
                            image = image_url.read()
                        with open(f'{lab["location"]}/assignment/{image_description["name"]}', mode='wb') as image_file:
                            image_file.write(image)
                            print(f'Saved {lab["location"]}/assignment/{image_description["name"]};'
                                  ' this might be the wrong location')
                    except urllib.error.HTTPError as exception:
                        print(f'Could not retrieve {image_description["link"]} for'
                              f' {lab["location"]}/assignment/{image_description["name"]}')
                        print(f'{exception}')
                        if 'search' in image_description and image_description['search'] is not None:
                            print('Consider an internet image search using the search term'
                                  f' {image_description["search"]}')
            case None:
                pass
            case _:
                print(f'Expected string or dictionary for image; got {image_description}')
    # create the Makefile
    makefile: str = f'LAB = {filename_core}\n\nlab: *.tex\n'
    if os.path.exists(f'{lab["location"]}/assignment/{filename_core}.bib'):
        makefile += '\tpdflatex $(LAB)\n\tbibtex   $(LAB)\n'
    makefile += ('\tpdflatex $(LAB)\n\tpdflatex $(LAB)\n\n'
                 'all: lab\n\n'
                 'clean:\n\trm -f $(LAB).aux $(LAB).log $(LAB).out $(LAB).synctex.gz $(LAB).toc $(LAB).bbl $(LAB).blg\n'
                 '\nclear: clean\n'
                 '\trm $(LAB).pdf\n')
    with open(f'{lab["location"]}/assignment/Makefile', mode='w') as output_file:
        output_file.write(makefile)


def prep_code(lab: Dict, storyline: Dict):
    # TODO: constraint-check
    executable: str = lab['lab'].lower()
    # starter code customization
    if 'lab-specific keys' in lab and lab['lab-specific keys'] is not None:
        globals()[f'generate_{executable}_starter_code'](lab, storyline)
    # create the Makefile
    compilation: Dict[str, Optional[Dict[str, str]]] = lab['compilation']
    makefile: str = (f'CC = {compilation["C"]["compiler"]}\n'
                     f'CFLAG = {compilation["C"]["optimization"]} '
                     f'-std={compilation["C"]["version"]} '
                     f'{compilation["C"]["warnings"]}\n'
                     f'LIB = {compilation["C"]["libraries"]}\n'
                     f'DEP = $(wildcard *.h) {compilation["C"]["additional dependencies"]}\n'
                     'OBJ := $(patsubst %.c,%.o,$(wildcard *.c))\n'
                     f'EXEC = {executable}\n\n'
                     f'%.o: %.c $(DEP)\n'
                     '\t$(CC) -c -o $@ $< $(CFLAG)\n\n'
                     f'{executable}: $(OBJ)\n'
                     '\t$(CC) -o $@ $^ $(CFLAG) $(LIB)\n\n'
                     'all: $(EXEC)\n\n'
                     'clean:\n'
                     '\trm -f $(OBJ) *~ core\n\n'
                     'clear: clean\n'
                     '\trm $(EXEC)\n')
    with open(f'{lab["location"]}/starter-code/Makefile', mode='w') as output_file:
        output_file.write(makefile)


def prep_labs(course: Dict, semester: Dict, labs: Dict, storyline: Dict, original_tex: str):
    for index, lab in enumerate(semester['labs']):
        complete_lab = lab | labs[lab['lab']]
        for category in course:
            if category not in complete_lab:
                complete_lab[category] = course[category]
            else:
                for default in course[category]:
                    if default not in complete_lab[category]:
                        complete_lab[category][default] = course[category][default]
                    elif isinstance(complete_lab[category][default], Dict):
                        for detail in course[category][default]:
                            if detail not in complete_lab[category][default]:
                                complete_lab[category][default][detail] = course[category][default][detail]
        previous_lab = semester['labs'][index - 1]['lab'] if index > 0 else None
        next_lab = semester['labs'][index + 1]['lab'] if index < len(semester['labs']) - 1 else None
        prep_latex(complete_lab, index + 1, semester['semester'], storyline,
                   previous_lab, next_lab, original_tex + '\n')
        prep_code(complete_lab, storyline)


if __name__ == '__main__':
    # TODO: specify a subset of the labs
    course_json = {}
    semester_json = {'labs': []}
    labs_json = {}
    storyline_json = {}
    try:
        with open('customization/course.json') as course_file:
            course_json = json.load(course_file)
        with open('customization/semester.json') as semester_file:
            semester_json = json.load(semester_file)
        with open('customization/labs.json') as labs_file:
            labs_json = json.load(labs_file)
        with open('customization/storylines/pleistocene-petting-zoo.json') as storyline_file:  # TODO: prompt for story
            storyline_json = json.load(storyline_file)
        with open('customization/assignment-definitions.tex') as definitions_file:
            definitions_tex = definitions_file.read()
        all_ready = True
    except FileNotFoundError as error:
        print(f'File not found: {error.filename}', file=sys.stderr)
        all_ready = False
    all_ready &= validate_labs_existence(semester_json['labs'], labs_json)
    if all_ready:
        prep_labs(course_json, semester_json, labs_json, storyline_json, definitions_tex)
        # TODO: build/package labs