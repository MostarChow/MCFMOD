const FMOD = cc.Class({
    statics: {
        // 测试
        test: 'event:/Music/Level 03',

        zhucheng: {'event': 'event:/MUSIC/music_switch', 'paramer': 'music switch', 'value': 0.0},
        senlin: {'event': 'event:/MUSIC/music_switch', 'paramer': 'music switch', 'value': 2.0},

        amb: 'event:/MUSIC/bgm_zhandou',

        load() {
            if (cc.sys.os === cc.sys.OS_IOS) {
                jsb.reflection.callStaticMethod('AppController', 'jsLoadBank');
            } else if (cc.sys.os === cc.sys.OS_ANDROID) {
                jsb.reflection.callStaticMethod('org/cocos2dx/javascript/AppActivity', 'jsLoadBank', '()V');
            }
        },
        playMusic(event) {
            if (cc.sys.os === cc.sys.OS_IOS) {
                jsb.reflection.callStaticMethod('AppController', 'jsPlayMusicEvent:andParamer:andValue:', event.event, event.paramer, event.value);
            } else if (cc.sys.os === cc.sys.OS_ANDROID) {
                jsb.reflection.callStaticMethod('org/cocos2dx/javascript/AppActivity', 'jsPlayMusicEvent', '(Ljava/lang/String;Ljava/lang/String;F)V', event.event, event.paramer, event.value);
            }
        },
        pauseMusic(event) {
            if (cc.sys.os === cc.sys.OS_IOS) {
                jsb.reflection.callStaticMethod('AppController', 'jsPauseMusicEvent:andParamer:andValue:', event.event, event.paramer, event.value);
            } else if (cc.sys.os === cc.sys.OS_ANDROID) {
                jsb.reflection.callStaticMethod('org/cocos2dx/javascript/AppActivity', 'jsPauseMusicEvent', '(Ljava/lang/String;Ljava/lang/String;F)V', event.event, event.paramer, event.value);
            }
        },
        resumeMusic(event) {
            if (cc.sys.os === cc.sys.OS_IOS) {
                jsb.reflection.callStaticMethod('AppController', 'jsResumeMusicEvent:andParamer:andValue:', event.event, event.paramer, event.value);
            } else if (cc.sys.os === cc.sys.OS_ANDROID) {
                jsb.reflection.callStaticMethod('org/cocos2dx/javascript/AppActivity', 'jsResumeMusicEvent', '(Ljava/lang/String;Ljava/lang/String;F)V', event.event, event.paramer, event.value);
            }
        },
        stopMusic(event) {
            if (cc.sys.os === cc.sys.OS_IOS) {
                jsb.reflection.callStaticMethod('AppController', 'jsStopMusicEvent:andParamer:andValue:', event.event, event.paramer, event.value);
            } else if (cc.sys.os === cc.sys.OS_ANDROID) {
                jsb.reflection.callStaticMethod('org/cocos2dx/javascript/AppActivity', 'jsStopMusicEvent', '(Ljava/lang/String;Ljava/lang/String;F)V', event.event, event.paramer, event.value);
            }
        },
        playEffect(event) {
            if (cc.sys.os === cc.sys.OS_IOS) {
                jsb.reflection.callStaticMethod('AppController', 'jsPlayEffectEvent:', event);
            } else if (cc.sys.os === cc.sys.OS_ANDROID) {
                jsb.reflection.callStaticMethod('org/cocos2dx/javascript/AppActivity', 'jsPlayEffectEvent', '(Ljava/lang/String;)V', event);
            }
        },
        stopEffect(event) {
            if (cc.sys.os === cc.sys.OS_IOS) {
                jsb.reflection.callStaticMethod('AppController', 'jsStopEffectEvent:', event);
            } else if (cc.sys.os === cc.sys.OS_ANDROID) {
                jsb.reflection.callStaticMethod('org/cocos2dx/javascript/AppActivity', 'jsStopEffectEvent', '(Ljava/lang/String;)V', event);
            }
        },
    }
});

module.exports = FMOD;