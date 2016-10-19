OPTION(ENABLE_OPENGL "Enable OpenGL support" ON)

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules) # FindGLFW3.cmake

# Out-of-tree build will have to have DLLs manually copied.
FIND_PACKAGE(freenect2 REQUIRED)
FIND_PACKAGE(GLFW3)
FIND_PACKAGE(OpenGL)
FIND_PACKAGE( OpenCV REQUIRED )
FIND_PACKAGE( OpenNI2 )
MESSAGE(STATUS "lib dir is"  ${OpenNI2_LIBRARY})

MESSAGE(STATUS "include dir is" ${freenect2_INCLUDE_DIR})

INCLUDE_DIRECTORIES(
  ${GLFW3_INCLUDE_DIRS}
  ${freenect2_INCLUDE_DIR}
  ${OpenNI2_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

ADD_DEFINITIONS(-DEXAMPLES_WITH_OPENGL_SUPPORT=1)# use OPENGL
ADD_EXECUTABLE(Protonect
  Protonect.cpp
  viewer.cpp
  flextGL.cpp
)
TARGET_LINK_LIBRARIES(Protonect
  ${freenect2_LIBRARIES}
  ${GLFW3_LIBRARIES}
  ${OPENGL_gl_LIBRARY}
)

ADD_EXECUTABLE(Protonect2
  Protonect2.cpp
)
TARGET_LINK_LIBRARIES(Protonect2
  ${freenect2_LIBRARIES}
  ${GLFW3_LIBRARIES}
  ${OpenCV_LIBS}
  ${OPENGL_gl_LIBRARY}
)

ADD_EXECUTABLE(openni2_drive2
  openni2_drive2.cpp
)
TARGET_LINK_LIBRARIES(openni2_drive2
  ${OpenCV_LIBS} 
  ${OpenNI2_LIBRARY}
)

ADD_EXECUTABLE(openni2_drive
  openni2_drive.cpp
)
TARGET_LINK_LIBRARIES(openni2_drive
  ${OpenCV_LIBS} 
  ${OpenNI2_LIBRARY}
)
#ADD_EXECUTABLE(simpleviewer
#  SimpleViewer/main.cpp
#  SimpleViewer/Viewer.cpp
#)
#TARGET_LINK_LIBRARIES(simpleviewer
#  ${PROJECT_SOURCE_DIR}/lib/glut32.lib
#  ${OpenCV_LIBS} 
#  ${OpenNI2_LIBRARIES}
  
#)


