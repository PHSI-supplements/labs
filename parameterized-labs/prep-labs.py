import functools
import json
import os
import shutil
import sys
from typing import Dict, List, Set, Optional


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


def prep_latex(lab: Dict, lab_number: int, course_term: str, storyline: Dict, tex: str):
    # TODO: copy storyline-related images, if any
    filename_core: str = lab['lab'].lower()
    # describe the course
    tex += f'\\newcommand{{\\institutename}}{{{lab["course information"]["institute"]}}}\n'
    tex += f'\\newcommand{{\\instructorname}}{{{lab["course information"]["instructor"]}}}\n'
    tex += f'\\newcommand{{\\coursenumber}}{{{lab["course information"]["course number"]}}}\n'
    # tex += f'\\newcommand{{\\cs2}}{{{lab["course information"]["cs2 course"]}}}\n'
    tex += f'\\newcommand{{\\courseterm}}{{{course_term}}}\n'
    # describe the assignment
    tex += f'\\newcommand{{\\labnumber}}{{{lab_number}}}\n'
    tex += f'\\newcommand{{\\labname}}{{{lab["lab name"]}}}\n'
    tex += f'\\newcommand{{\\shortlabname}}{{{lab["lab"]}}}\n'
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
    tex += f'\\newcommand{{\\policyforcodethatdoesnotcompile}}{{{lab["policies"]["grading"]["uncompilable"]}}}'
    tex += f'\\newcommand{{\\latepolicy}}{{{lab["policies"]["grading"]["late"]}}}'
    tex += \
        f'\\newcommand{{\\softwareengineeringfrontmatter}}{{{lab["policies"]["software engineering"][0]["policy"]}}}\n'
    tex += \
        f'\\newcommand{{\\softwareengineeringpenalties}}{{{lab["policies"]["software engineering"][0]["penalty"]}}}\n'
    # TODO: handle additional SE elements
    # storyline
    scenario_introduction: str = f'{storyline["story introduction"]}\n{storyline[lab["lab"]]["introduction"]}' \
        if lab_number == 1 else f'{storyline[lab["lab"]]["introduction"]}'
    tex += f'\\newcommand{{\\scenariointroduction}}{{{scenario_introduction}}}\n'
    tex += f'\\newcommand{{\\scenariowrapup}}{{{storyline[lab["lab"]]["wrapup"]}}}\n'
    if 'introduction image' in storyline.keys() and storyline['introduction image'] is not None:
        if os.path.isfile(f'customization/storylines/{storyline["introduction image"]}'):
            shutil.copy(src=f'customization/storylines/{storyline["introduction image"]}',
                        dst=f'{lab["location"]}/assignment/', follow_symlinks=True)
        else:
            print(f'No such file for introduction image: customization/storylines/{storyline["introduction image"]}')
    # TODO: handle scenario images
    # TODO: handle internet-sourced images
    # TODO: handle storyline conclusion
    # TODO: handle teasers and callbacks
    # output the LaTeX customization
    with open(f'{lab["location"]}/assignment/assignment-definitions.tex', mode='w') as output_file:
        output_file.write(tex)
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


def prep_code(lab: Dict):
    executable: str = lab['lab'].lower()
    # create the Makefile
    compilation: Dict[str, Optional[Dict[str, str]]] = lab['compilation']
    makefile: str = (f'CC = {compilation["C"]["compiler"]}\n'
                     f'CFLAG = {compilation["C"]["optimization"]} -std={compilation["C"]["version"]} {compilation["C"]["warnings"]}\n'
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
        prep_latex(complete_lab, index + 1, semester['semester'], storyline, original_tex + '\n')
        prep_code(complete_lab)


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
