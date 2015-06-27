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