# Initial Setup

## The Course's First Lab

I use the first lab to have students set up their development environment, including parts they won't use until later in the semester,
and to do a simple assignment that serves as an introduction (or re-familiarization) of C and a couple of its features that can be surprising.
PokerLab serves for the second purpose.

I like to keep the code portion of it simple for two reasons.
First, it allows students to focus on the novelty of integers-as-booleans and of pointers, without getting lost in more complex logic.
Second, it's small enough that students who are late to arrive for the semester (typically to get cheaper airfares) can quickly catch up.
If your students are all already familiar with C and you don't have students arrive for the semester late, then you could use a more challenging assignment, such as ListLab.

Whichever code assignment you use, first students need to get their development environment set up.

## Providing Instructions for Setting Up the Development Environment

If you distribute assignments through Git repositories, then you have a bootstrapping problem:
You need to distribute the instructions for setting up the environment (including the repository) before students have access to the repository you created (or, alternatively, before the students provide you with access to a repository they created).
For this reason, I've separated the instructions for setting up the environment from the code assignment.

I've provided an [example](UNL-CSCE231/UNL-CSCE231-setup.md) set of instructions.
Feel free to adapt it to how you like to run your course, or write entirely new instructions if the example is too far removed from your preferences.
You can then copy the rendered instructions into an assignment on your LMS, solving your bootstrapping problem.
