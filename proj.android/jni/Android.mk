LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/data/GCache.cpp \
                   ../../Classes/data/GJson.cpp \
                   ../../Classes/model/GBullet.cpp \
                   ../../Classes/model/GEnemy.cpp \
                   ../../Classes/model/GHero.cpp \
                   ../../Classes/model/GLevel.cpp \
                   ../../Classes/scene/GGameScene.cpp \
                   ../../Classes/scene/GHomeScene.cpp \
                   ../../Classes/scene/GMainScene.cpp \
                   ../../Classes/scene/GScene.cpp \
                   ../../Classes/sprite/GBulletSprite.cpp \
                   ../../Classes/sprite/GDropSprite.cpp \
                   ../../Classes/sprite/GEnemySprite.cpp \
                   ../../Classes/sprite/GHeroSprite.cpp \
                   ../../Classes/sprite/GSprite.cpp \
                   ../../Classes/tools/GTools.cpp \
                   ../../Classes/ui/GAbout.cpp \
                   ../../Classes/ui/GAd.cpp \
                   ../../Classes/ui/GRockView.cpp \
                   ../../Classes/ui/GTouchLayer.cpp \
                   ../../Classes/ui/GUIGameOver.cpp \
                   ../../Classes/ui/GUILevel.cpp \
                   ../../Classes/ui/GUIRole.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
