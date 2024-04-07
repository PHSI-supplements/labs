import functools
import json
import os
import shutil
import sys
import urllib.error
import urllib.request
from typing import Dict, List, Set, Optional, Union


def validate_labs_existence(semester: List[Dict], labs: Dict) -> bool:
    semester_labs: Set[str] = {lab['lab'] for lab in semester}
    missing_labs = semester_labs - labs.keys()
    if missing_labs:
        print(f'Missing data for: {missing_labs}', file=sys.stderr)
        validated = False
    else:
        composite_labs: List[Dict] = [lab for lab in semester if labs[lab['lab']]['location'] == 'composite']
        lab_locations: List[str] = [labs[lab['lab']]['location'] for lab in semester
                                    if labs[lab['lab']]['location'] not in {'composite', 'TODO'}]
        for lab in composite_labs:
            lab_locations += labs[lab['lab']]['locations']
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


# TODO: Move lab-specific functions to lab-specific directories,
#  and dynamically-import the code using __import__() and possibly get_attr()
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
    latex_newline_replacement = '\\nl '
    c_newline_replacement = '\\textbackslash n'
    email: str = ''
    for line in message.split('\n'):
        email += f'\\texttt{{{line.replace(tab_character, latex_tab_replacement)}{latex_newline_replacement}}} \\\\'
    c_function = ''
    for line in message.split('\n'):
        c_function += ('\\texttt{{\\phantom{{xxxxxxxxxxxx}}"'
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


# noinspection PyUnusedLocal
def prep_latex(lab: Dict, lab_number: int, course_term: str, storyline: Dict,
               previous_lab: Optional[str], next_lab: Optional[str], tex: str):
    short_labname = lab['lab']
    filename_core: str = short_labname.lower()
    # describe the course
    tex += f'\\newcommand{{\\institutename}}{{{lab["course information"]["institute"]}}}\n'
    tex += f'\\newcommand{{\\instructorname}}{{{lab["course information"]["instructor"]}}}\n'
    tex += f'\\newcommand{{\\coursenumber}}{{{lab["course information"]["course number"]}}}\n'
    tex += f'\\newcommand{{\\cstwo}}{{{lab["course information"]["cs2 course"]}}}\n'
    # TODO: separate "cs2 course" into "linked structures course" and "GUI intro course",
    #  and maybe also "sort intro course" and "big O course"
    tex += f'\\newcommand{{\\courseterm}}{{{course_term}}}\n'
    # describe the assignment
    tex += f'\\newcommand{{\\labnumber}}{{{lab_number}}}\n'
    tex += f'\\newcommand{{\\labname}}{{{lab["lab name"]}}}\n'
    tex += f'\\newcommand{{\\shortlabname}}{{{short_labname}}}\n'
    tex += f'\\newcommand{{\\duedate}}{{{lab["due"]}}}\n'
    if lab["location"] == 'composite':
        for index, location in enumerate(lab["locations"][1:]):
            # number_string = inflect.engine.number_to_words(index + 1)  # there seems to be a bug in the inflect module
            number_string: str
            match index + 1:
                case 1:
                    number_string = 'one'
                case 2:
                    number_string = 'two'
                case 3:
                    number_string = 'three'
                case _:
                    number_string = 'unknown'
            tex += f'\\newcommand{{\\path{number_string}}}{{{location}}}\n'
    # file flow
    tex += f'\\newcommand{{\\filesource}}{{{lab["file flow"]["source"]}}}\n'
    tex += f'\\newcommand{{\\filesubmission}}{{{lab["file flow"]["submission"]}}}\n'
    tex += f'\\newcommand{{\\runtimeenvironment}}{{{lab["file flow"]["runtime environment"]}}}\n'
    tex += f'\\newcommand{{\\startercode}}{{{filename_core}.zip or {filename_core}.tar}}\n'
    tex += f'\\newcommand{{\\requiredfiles}}{{{lab["required files"]}}}\n'.replace('_', '\\_')
    # particulars about the environment
    tex += f'\\newcommand{{\\buildsystem}}{{{lab["compilation"]["buildsystem"]}}}\n'
    tex += f'\\newcommand{{\\processor}}{{{lab["compilation"]["processor"]}}}\n'
    tex += f'\\newcommand{{\\lowercaseprocessor}}{{{lab["compilation"]["processor"]}}}\n'.lower()
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
    lab_location = lab['locations'][0] if 'locations' in lab else lab['location']
    with open(f'{lab_location}/assignment/assignment-definitions.tex', mode='w') as output_file:
        output_file.write(tex)
    # copy any necessary images
    images: List[Union[str, Dict[str, str]]] = lab['images'] if 'images' in lab else []
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
                                dst=f'{lab_location}/assignment/', follow_symlinks=True)
                else:
                    print('No such file for introduction image:'
                          f' customization/storylines/{storyline["introduction image"]}')
            case dict():
                if 'link' in image_description and image_description['link'] is not None:
                    try:
                        with urllib.request.urlopen(image_description["link"]) as image_url:
                            image = image_url.read()
                        with open(f'{lab_location}/assignment/{image_description["name"]}', mode='wb') as image_file:
                            image_file.write(image)
                            print(f'Saved {lab_location}/assignment/{image_description["name"]};'
                                  ' this might be the wrong location')
                    except urllib.error.HTTPError as exception:
                        print(f'Could not retrieve {image_description["link"]} for'
                              f' {lab_location}/assignment/{image_description["name"]}')
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
    if os.path.exists(f'{lab_location}/assignment/{filename_core}.bib'):
        makefile += '\tpdflatex $(LAB)\n\tbibtex   $(LAB)\n'
    makefile += ('\tpdflatex $(LAB)\n\tpdflatex $(LAB)\n\n'
                 'all: lab\n\n'
                 'clean:\n\trm -f $(LAB).aux $(LAB).log $(LAB).out $(LAB).synctex.gz'
                 ' $(LAB).toc $(LAB).bbl $(LAB).blg $(LAB).fls $(LAB).fdb_latexmk\n'
                 '\nclear: clean\n'
                 '\trm $(LAB).pdf\n')
    with open(f'{lab_location}/assignment/Makefile', mode='w') as output_file:
        output_file.write(makefile)


def create_makefile(lab: Dict) -> None:
    handle: str = lab['lab'].lower()
    compilation: Dict[str, Union[Dict[str, str], List[Dict[str, str], None]]] = lab['compilation']
    targets: List[Dict[str, str]]
    if compilation['C']['custom targets'] is None:
        targets = [{
            "target": handle,
            "dependencies": "$(OBJ)"
        }]
    else:
        targets = compilation['C']['custom targets']
    executable_names = str.join(' ', [target['target'] for target in targets])
    target_lines = ''
    for target in targets:
        target_lines += f'{target["target"]}: {target["dependencies"]}\n\t$(CC) -o $@ $^ $(CFLAG) $(LIB) $(OPTION)\n\n'
    makefile: str = (f'CC = {compilation["C"]["compiler"]}\n'
                     f'CFLAG = {compilation["C"]["optimization"]} '
                     f'-std={compilation["C"]["standard"]} '
                     f'{compilation["C"]["warnings"]}\n'
                     f'LIB = {compilation["C"]["libraries"]}\n'
                     f'DEP = $(wildcard *.h) {compilation["C"]["additional dependencies"]}\n'
                     f'OBJ := $(patsubst %.c,%.o,$(wildcard *.c))')
    if compilation["asm"]["suffix"] is not None:
        makefile += f' $(patsubst %{compilation["asm"]["suffix"]},%.o,$(wildcard *{compilation["asm"]["suffix"]}))'
    makefile += ('\n'
                 f'EXEC = {executable_names}\n\n'
                 f'%.o: %.c $(DEP)\n'
                 '\t$(CC) -c -o $@ $< $(CFLAG) $(OPTION)\n\n')
    if compilation["asm"]["suffix"] is not None:
        makefile += (f'%.o: %{compilation["asm"]["suffix"]} $(DEP)\n'
                     '\t$(CC) -c -o $@ $< $(CFLAG) $(OPTION)\n\n')
    makefile += (f'{target_lines}'
                 'all: $(EXEC)\n\n'
                 'clean:\n'
                 '\trm -f $(OBJ) *~ core\n\n'
                 'clear: clean\n'
                 '\trm $(EXEC)\n')
    with open(f'{lab["location"]}/starter-code/Makefile', mode='w') as output_file:
        output_file.write(makefile)


def create_platformio_ini(lab: Dict) -> None:
    compilation: Dict[str, Union[Dict[str, str], List[Dict[str, str], None]]] = lab['compilation']
    targets: List[Dict[str, str]]
    match compilation['processor']:
        case 'ATmega328P':
            targets = [
                {'environment': 'nanoatmega328old', 'platform': 'atmelavr',
                 'board': 'nanoatmega328', 'framework': 'arduino'},
                {'environment': 'nanoatmega328new', 'platform': 'atmelavr',
                 'board': 'nanoatmega328new', 'framework': 'arduino'},
                {'environment': 'uno', 'platform': 'atmelavr',
                 'board': 'uno', 'framework': 'arduino'}
            ]
        case 'RP2040':
            targets = [
                {'environment': 'pico', 'platform': 'raspberrypi', 'board': 'pico', 'framework': 'arduino'}
            ]
        case _:
            raise ValueError(f'Unknown processor: {compilation["processor"]}')
    platformio_ini: str = '; PlatformIO Project Configuration File\n\n'
    platformio_ini += f'[env]\nlib_deps =\n{compilation["C"]["libraries"]}\n\n'
    for target in targets:
        platformio_ini += (f'[env:{target["environment"]}]\n'
                           f'platform = {target["platform"]}\n'
                           f'board = {target["board"]}\n'
                           f'framework = {target["framework"]}\n'
                           'build_src_flags =')
        # we'll ignore the compiler key and the additional dependencies key
        if compilation['C']['standard'] != '':
            platformio_ini += f' -std={compilation["C"]["standard"]}\n'
        for flag in ['optimization', 'warnings']:
            platformio_ini += f' {compilation["C"][flag]}'
        platformio_ini += '\n\n'
    lab_location = lab['locations'][0] if 'locations' in lab else lab['location']
    with open(f'{lab_location}/starter-code/{lab["lab"]}/platformio.ini', mode='w') as output_file:
        output_file.write(platformio_ini)


def compose_starter_code(lab: Dict) -> None:
    destination: str = f'{lab["locations"][0]}/starter-code/PollingLab'
    for location in lab['locations'][1:]:
        source = f'{location}/starter-code'
        if os.path.exists(source):
            shutil.copytree(src=source, dst=destination, dirs_exist_ok=True)
        source += f'-{lab["compilation"]["processor"].lower()}'
        if os.path.exists(source):
            shutil.copytree(src=source, dst=destination, dirs_exist_ok=True)


def prep_code(lab: Dict, storyline: Dict):
    # TODO: constraint-check
    handle: str = lab['lab'].lower()
    # starter code customization
    if 'lab-specific keys' in lab and lab['lab-specific keys'] is not None:
        globals()[f'generate_{handle}_starter_code'](lab, storyline)
    if lab['location'] == 'composite':
        compose_starter_code(lab)
    # create the build file
    if lab["compilation"]["buildsystem"] == 'make':
        create_makefile(lab)
    if lab["compilation"]["buildsystem"] == 'platformio':
        create_platformio_ini(lab)


def prep_labs(course: Dict, semester: Dict, labs: Dict, storyline: Dict, labs_to_process: List[str], original_tex: str):
    for index, lab in enumerate(semester['labs']):
        if lab['lab'] in labs_to_process:
            complete_lab = lab | labs[lab['lab']]
            if 'locations' in complete_lab:
                complete_lab['locations'] = labs[lab['lab']]['locations'] + lab['locations']
            for category in course:
                if category not in complete_lab:
                    complete_lab[category] = course[category]
                else:
                    for default in course[category]:
                        if category in semester['labs'][index] and default in semester['labs'][index][category]:
                            complete_lab[category][default] = semester['labs'][index][category][default]
                        if default not in complete_lab[category]:
                            complete_lab[category][default] = course[category][default]
                        elif isinstance(complete_lab[category][default], Dict):
                            for detail in course[category][default]:
                                if (default in semester['labs'][index][category]
                                        and detail in semester['labs'][index][category][default]):
                                    complete_lab[category][default][detail] =\
                                        semester['labs'][index][category][default][detail]
                                if detail not in complete_lab[category][default]:
                                    complete_lab[category][default][detail] = course[category][default][detail]
            previous_lab = semester['labs'][index - 1]['lab'] if index > 0 else None
            next_lab = semester['labs'][index + 1]['lab'] if index < len(semester['labs']) - 1 else None
            prep_latex(complete_lab, index + 1, semester['semester'], storyline,
                       previous_lab, next_lab, original_tex + '\n')
            prep_code(complete_lab, storyline)


if __name__ == '__main__':
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
        # TODO: prompt for story -- or make that part of semester.json
        with open('customization/storylines/pleistocene-petting-zoo.json') as storyline_file:
            storyline_json = json.load(storyline_file)
        with open('customization/assignment-definitions.tex') as definitions_file:
            definitions_tex = definitions_file.read()
        all_ready = True
    except FileNotFoundError as error:
        print(f'File not found: {error.filename}', file=sys.stderr)
        all_ready = False
    all_ready &= validate_labs_existence(semester_json['labs'], labs_json)
    labs_subset = sys.argv[1:] if len(sys.argv) > 1 else [lab['lab'] for lab in semester_json['labs']]
    if all_ready:
        prep_labs(course_json, semester_json, labs_json, storyline_json, labs_subset, definitions_tex)
        # TODO: build/package labs
