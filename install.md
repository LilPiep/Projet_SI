# Install party for GLFW, please take a look

source : https://stackoverflow.com/questions/17768008/how-to-build-install-glfw-3-and-use-it-in-a-linux-project

## 2020 Updated Answer

It is 2020 (7 years later) and I have learned more about Linux during this time. Specifically that it might not be a good idea to run sudo make install when installing libraries, as these may interfere with the package management system. (In this case apt as I am using Debian 10.)

If this is not correct, please correct me in the comments.
Alternative proposed solution

This information is taken from the GLFW docs, however I have expanded/streamlined the information which is relevant to Linux users.

### Go to home directory and clone glfw repository from github

```ash
cd ~
git clone https://github.com/glfw/glfw.git
cd glfw
```

    You can at this point create a build directory and follow the instructions here (glfw build instructions), however I chose not to do that. The following command still seems to work in 2020 however it is not explicitly stated by the glfw online instructions.

```bash
cmake -G "Unix Makefiles"
```

    You may need to run sudo apt-get build-dep glfw3 before (?). I ran both this command and sudo apt install xorg-dev as per the instructions.

    Finally run make

    Now in your project directory, do the following. (Go to your project which uses the glfw libs)

    Create a CMakeLists.txt, mine looks like this

```
CMAKE_MINIMUM_REQUIRED(VERSION 3.7)
PROJECT(project)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_BUILD_TYPE DEBUG)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(/home/<user>/glfw /home/<user>/glfw/src)


FIND_PACKAGE(OpenGL REQUIRED)

SET(SOURCE_FILES main.cpp)

ADD_EXECUTABLE(project ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(project glfw)
TARGET_LINK_LIBRARIES(project OpenGL::GL)
```

    If you don't like CMake then I appologize but in my opinion it is the easiest way to get your project working quickly. I would recommend learning to use it, at least to a basic level. Regretably I do not know of any good CMake tutorial

    Then do cmake . and make, your project should be built and linked against glfw3 shared lib

    There is some way of creating a dynamic linked lib. I believe I have used the static method here. Please comment / add a section in this answer below if you know more than I do

    This should work on other systems, if not let me know and I will help if I am able to

