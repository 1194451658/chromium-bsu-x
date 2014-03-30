
DEBUG = 1
USE_BOX2D = 1
OPENAL = 1

EXECUTABLE = HelloCpp

INCLUDES = -I.. -I../Classes

SOURCES = main.cpp \
        ../Classes/AppDelegate.cpp \
        ../Classes/HelloWorldScene.cpp \
	../Classes/aircraft/HeroAircraft.cpp \
	../Classes/aircraft/EnemyAircraft0.cpp \
	../Classes/aircraft/Aircraft.cpp \
	../Classes/input/InputManager.cpp \
	../Classes/physics/GLES-Render.cpp \
	../Classes/physics/GB2ShapeCache-x.cpp \
	../Classes/physics/PhysicsManager.cpp \
	../Classes/GameObject.cpp \
	../Classes/gun/HeroDefaultGun.cpp \
	../Classes/gun/GunFactory.cpp \
	../Classes/gun/Gun.cpp \
	../Classes/gun/shotMethod/LateralShot.cpp \
	../Classes/gun/Ammo.cpp \



COCOS_ROOT = ../../..
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

INCLUDES += -I${COCOS_SRC}/../external \
	    -I${COCOS_SRC}/../CocosDenshion/include \



SHAREDLIBS += -lcocos2d \
	      -lbox2d \
	      -lcocosdenshion \



COCOS_LIBS = $(LIB_DIR)/libcocos2d.so \
	     $(LIB_DIR)/libbox2d.a \
	     $(LIB_DIR)/libcocosdenshion.so \



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

