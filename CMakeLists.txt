PROJECT (ReactionTime)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6 FATAL_ERROR)

FIND_PACKAGE (Qt4 REQUIRED)

SET (ReactionTime_SOURCES main.cpp reactiontime.cpp)
SET (ReactionTime_HEADERS reactiontime.h)
SET (ReactionTime_FORMS reactiontime.ui)

INCLUDE (${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

QT4_WRAP_CPP (ReactionTime_HEADERS_MOC ${ReactionTime_HEADERS})
QT4_WRAP_UI (ReactionTime_FORMS_HEADERS ${ReactionTime_FORMS})

ADD_EXECUTABLE (ReactionTime ${ReactionTime_SOURCES} 
                             ${ReactionTime_HEADERS_MOC}
                             ${ReactionTime_FORMS_HEADERS})
TARGET_LINK_LIBRARIES(ReactionTime ${QT_LIBRARIES})
