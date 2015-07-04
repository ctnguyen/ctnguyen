/************************************************
*     Mini Porject for cmake test full feature  *
*     Use of cmake, cTest, cPack, Dashboard     *
*     @authors Chi Thanh NGUYEN                 *
*     contact chithanhnguyen.math@gmail.com     *
*************************************************/

The objective is to able to create a cross plateform, 
with full use of cmake, ctest, cPack :
1. - ability of creating project with a featured folder hierarchie in MVSC++
2. - ability of creating package, install with dynamic path handling
3. - ability of automatic running test, report them to a dashboard (CDash, Jenkins ..)


- Project tree in VC++ has the predefined hierarchical. 
- Libs are generated both as dynamics and static
- VC++ solution has to be crossconfig, i.e Debug and Release in the same solution
  In future, might be also cross buildtype, i.e x86 and x64 in the same solution
- modular doxygen generation, depending on module choosen from a build config.

The projec tree in VC++ should be
.
.LibNumber (folder)
.  Proj1
.  Proj2
.LibLetter (folder)
.  ProjA
.  ProjB
.Applications (folder)
.  Prog1A
.  Prog2B
.Test (folder)
.  Unit (folder)
.    test_Proj1
.    test_Proj2
.    test_ProjA
.    test_ProjB
.  Acceptance (folder)
.    test_LongTime1
.    test_LongTime2

TODO :
- Make compile dll and lib, 
- Make linking a projet with Qt, (focus on config, buildtype dependency and link with the right Qt) x64,x86,Debug,Release
- Try to install and packaging (need internal and external dependancy, only the neccessaries one)
- Cpack with different component config (at least two)
- If have time, separate lib/bin folder (executable should be in the root build directory).


- Make ctest works, for unit test, for long test. 
- Make tests works with DashBoard (Jenkins or CDash)

- Test on cross plateform Linux, Mac OS, MVSC++, Qt Creator, Xcode

- Read about resource file, possibility of use .qrc instead of plateform dependand like .rc only for VC++
- Run Ancoa build with one processor, and save build log, to see the order of dependency.



