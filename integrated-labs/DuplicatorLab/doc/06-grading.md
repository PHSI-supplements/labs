> 📇 **Epilogue**
>
> Between H.Awk trying to sell samples to a competitor, that weird guy almost blowing up the zoo, and the animals almost escaping, Archie is getting worried.
> I think we need to introduce additional protective measures.
> As useful as your challenge-response app is in helping us detect intruders, I think it's now clear that we need something that will keep someone -- or some*thing* -- out of places they shouldn't be, even when no one else is around.
> I've asked the team at Eclectic Electronics to put something together."
> 
> *To be continued...*

## Turn-In and Grading

Be sure that you have pushed your code to git.unl.edu.

### No Credit for Uncompilable Code

If the TA cannot create an executable from your code, then your code will be assumed to have no functionality.
Be sure to compile and test your code on the nuros.unl.edu Linux server with the original driver code, the original header file(s), and the original CMake configuration files.

> ✍️ **One Edit Rule**
>
> At the TA's discretion, if they can make your code compile with one edit (such as introducing a missing semicolon) then they may do so and then assess a 10% penalty on the resulting score.
> The TA is under no obligation to do so, and you should not rely on the TA’s willingness to edit your code for grading.
> If there are multiple options for a single edit that would make your code compile, there is no guarantee that the TA will select the option that would maximize your score.

### Late Submissions

This assignment is due before the start of your lab section.
If you have late days available, you may use one or more to extend your deadline.
You can exercise a late day (or days) by editing the [LATE-DAYS-USED-ON-THIS-ASSIGNMENT.txt](../LATE-DAYS-USED-ON-THIS-ASSIGNMENT.txt) file and including the update with your code.

After you have exhausted your late days, we will accept late turn-ins up to one hour late, assessing a 10% penalty on these late submissions.
After you have exhausted your late days, any work turned in more than one hour late will not be graded.

### Rubric

This assignment is worth 20 points.

- In *answers.txt*:
  - [ ] **+3** Provides a valid interleaving that produces the specified output
  - [ ] **+2** Proposes reasonable locations to lock the mutex
  - [ ] **+2** Proposes reasonable locations to unlock the mutex
  - [ ] **+2** Demonstrates that the proposed changes would prevent the shared buffer from being prematurely overwritten
- In *duplicator.c*:
  - [ ] **+2** Correctly initializes and destroys the mutex
  - [ ] **+2** Correctly locks and unlocks the mutex…
  - [ ] **+1** … and does so in the locations that are identified in *answers.txt*
  - [ ] **+3** The duplicator makes correct copies
  - [ ] **+3** No thread starves
- Penalties:
  - [ ] **-1** for each line of code added other than calls to `pthread_mutex_init()`, `pthread_mutex_destroy()`, `pthread_mutex_lock()`, and `pthread_mutex_unlock()`
  - [ ] **-1** for each line of the starter code edited, moved, or deleted

---

|            [⬅️](05-remove-race-condition.md)             |      [⬆️](../README.md)      |                              |
|:--------------------------------------------------------:|:----------------------------:|:----------------------------:|
| [Remove the Race Condition](05-remove-race-condition.md) | [Front Matter](../README.md) |                              |
