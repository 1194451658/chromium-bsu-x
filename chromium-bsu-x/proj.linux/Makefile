
DEBUG = 1
USE_BOX2D = 1
OPENAL = 1

EXECUTABLE = HelloCpp

INCLUDES = -I.. -I../Classes

SOURCES = main.cpp \
	../Classes/aircraft/Aircraft.cpp \
	../Classes/aircraft/EnemyBoss00.cpp \
	../Classes/aircraft/EnemyOmni.cpp \
	../Classes/aircraft/EnemyStraight.cpp \
	../Classes/aircraft/HeroAircraft.cpp \
	../Classes/engine/action/CCRandomRotateBy.cpp \
	../Classes/engine/action/CCRandTextureCoord.cpp \
	../Classes/engine/CCDrawGameObjectShadowNode.cpp \
	../Classes/engine/CCSpriteWithShadow.cpp \
	../Classes/gun/coldTimeMethod/EqualColdTime.cpp \
	../Classes/gun/coldTimeMethod/GroupShotColdTimeMethod.cpp \
	../Classes/gun/shotMethod/LateralShotMethod.cpp \
	../Classes/gun/shotMethod/MiddleShotMethod.cpp \
	../Classes/gun/shotMethod/SineShotMethod.cpp \
	../Classes/gun/shotMethod/StrafeShotMethod.cpp \
	../Classes/gun/shotMethod/SwapLateralShotMethod.cpp \
	../Classes/gun/shotMethod/TargetHeroShotMethod.cpp \
	../Classes/gun/Gun.cpp \
	../Classes/gun/Ammo.cpp \
	../Classes/input/InputManager.cpp \
	../Classes/map/AutoTiledBackground.cpp \
	../Classes/map/Map1.cpp \
	../Classes/physics/GLES-Render.cpp \
	../Classes/physics/GB2ShapeCache-x.cpp \
	../Classes/physics/PhysicsManager.cpp \
	../Classes/scene/TestAircraft.cpp \
	../Classes/scene/TestArmatureScene.cpp \
	../Classes/scene/TestControl.cpp \
	../Classes/scene/TestEffect.cpp \
	../Classes/scene/TestPhysicsManager.cpp \
	../Classes/scene/TestShotMethod.cpp \
	../Classes/GameObject.cpp \
	../Classes/GameController.cpp \
        ../Classes/AppDelegate.cpp \
        ../Classes/HelloWorldScene.cpp \


COCOS_ROOT = ../../..
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

INCLUDES += -I${COCOS_SRC}/../external \
	    -I${COCOS_SRC}/../extensions \
	    -I${COCOS_SRC}/../CocosDenshion/include \


SHAREDLIBS += -lcocos2d \
	      -lbox2d \
	      -lcocosdenshion \
	      -lextension \

COCOS_LIBS = $(LIB_DIR)/libcocos2d.so \
	     $(LIB_DIR)/libbox2d.a \
	     $(LIB_DIR)/libcocosdenshion.so \
	     $(LIB_DIR)/libextension.a




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

