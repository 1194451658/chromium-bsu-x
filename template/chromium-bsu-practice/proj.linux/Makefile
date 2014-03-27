
DEBUG = 1
USE_BOX2D = 1

EXECUTABLE = HelloCpp

INCLUDES = -I.. -I../Classes

SOURCES = main.cpp \
        ../Classes/AppDelegate.cpp \
        ../Classes/HelloWorldScene.cpp \
	../Classes/aircraft/heroAircraft.cpp \
	../Classes/aircraft/EnemyAircraft0.cpp \
	../Classes/aircraft/Aircraft.cpp \
	../Classes/input/InputManager.cpp \
	../Classes/util/GLES-Render.cpp \
	../Classes/util/GB2ShapeCache-x.cpp \
	../Classes/physics/PhysicsManager.cpp \
	../Classes/GameObject.cpp \
	../Classes/gun/HeroDefaultGun.cpp \
	../Classes/ammo/Ammo.cpp \









COCOS_ROOT = ../../..
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

INCLUDES += -I${COCOS_SRC}/../external

SHAREDLIBS += -lcocos2d \
	      -lbox2d \


COCOS_LIBS = $(LIB_DIR)/libcocos2d.so \
	     $(LIB_DIR)/libbox2d.a \


$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

debug:
	./bin/debug/HelloCpp

