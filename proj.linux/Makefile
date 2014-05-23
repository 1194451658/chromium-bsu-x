
DEBUG = 1
USE_BOX2D = 1
OPENAL = 1

EXECUTABLE = HelloCpp

INCLUDES = -I.. -I../Classes

SOURCES = main.cpp \
	../Classes/aircraft/Aircraft.cpp \
	../Classes/aircraft/EnemyBoss00.cpp \
	../Classes/aircraft/EnemyBoss01.cpp \
	../Classes/aircraft/EnemyOmni.cpp \
	../Classes/aircraft/EnemyStraight.cpp \
	../Classes/aircraft/EnemyRayGun.cpp \
	../Classes/aircraft/HeroAircraft.cpp \
	../Classes/engine/action/CCRandomRotateBy.cpp \
	../Classes/engine/action/CCRandTextureCoord.cpp \
	../Classes/engine/input/InputManager.cpp \
	../Classes/engine/physics/DebugDrawBox2dLayer.cpp \
	../Classes/engine/physics/GB2ShapeCache-x.cpp \
	../Classes/engine/physics/GLES-Render.cpp \
	../Classes/engine/physics/PhysicsManager.cpp \
	../Classes/engine/sprite_nodes/CCSpriteExt.cpp \
	../Classes/engine/sprite_nodes/CCSpriteExtWithShadow.cpp \
	../Classes/engine/tinyxml2/tinyxml2utils.cpp \
	../Classes/engine/xfl/XflParser.cpp \
	../Classes/engine/CCDrawGameObjectShadowNode.cpp \
	../Classes/engine/CCSpriteWithShadow.cpp \
	../Classes/engine/GameObject.cpp \
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
	../Classes/map/trigger/EnterScreenTrigger.cpp \
	../Classes/map/AutoTiledBackground.cpp \
	../Classes/map/Map.cpp \
	../Classes/scene/GameScene.cpp \
	../Classes/test/engine/TestPhysicsEditor.cpp \
	../Classes/test/engine/TestPhysicsManager.cpp \
	../Classes/test/originalEngine/TestArmatureScene.cpp \
	../Classes/test/originalEngine/TestBox2d.cpp \
	../Classes/test/originalEngine/TestControl.cpp \
	../Classes/test/originalEngine/TestTinyXml.cpp \
	../Classes/test/other/TestFallingLeaf.cpp \
	../Classes/test/TestAircraft.cpp \
	../Classes/test/TestAutoTiledMap.cpp \
	../Classes/test/TestEffect.cpp \
	../Classes/test/TestMapAndTrigger.cpp \
	../Classes/test/TestShotMethod.cpp \
        ../Classes/AppDelegate.cpp \
	../Classes/GameController.cpp \
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

