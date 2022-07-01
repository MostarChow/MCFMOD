const FMOD = cc.Class({
    statics: {
        // 测试
        test: 'event:/Music/Level 03',

        load() {
            if (cc.sys.os === cc.sys.OS_IOS) {
                jsb.reflection.callStaticMethod('AppController', 'jsLoadBank');
            } else if (cc.sys.os === cc.sys.OS_ANDROID) {
                jsb.reflection.callStaticMethod('org/cocos2dx/javascript/AppActivity', 'jsLoadBank', '()V');
            }
        },
        play(event) {
            if (cc.sys.os === cc.sys.OS_IOS) {
                jsb.reflection.callStaticMethod('AppController', 'jsPlayEvent:', event);
            } else if (cc.sys.os === cc.sys.OS_ANDROID) {
                jsb.reflection.callStaticMethod('org/cocos2dx/javascript/AppActivity', 'jsPlayEvent', '(Ljava/lang/String;)V', event);
            }
        },
        pause(event) {
            if (cc.sys.os === cc.sys.OS_IOS) {
                jsb.reflection.callStaticMethod('AppController', 'jsPauseEvent:', event);
            } else if (cc.sys.os === cc.sys.OS_ANDROID) {
                jsb.reflection.callStaticMethod('org/cocos2dx/javascript/AppActivity', 'jsPauseEvent', '(Ljava/lang/String;)V', event);
            }
        },
        resume(event) {
            if (cc.sys.os === cc.sys.OS_IOS) {
                jsb.reflection.callStaticMethod('AppController', 'jsResumeEvent:', event);
            } else if (cc.sys.os === cc.sys.OS_ANDROID) {
                jsb.reflection.callStaticMethod('org/cocos2dx/javascript/AppActivity', 'jsResumeEvent', '(Ljava/lang/String;)V', event);
            }
        },
        stop(event) {
            if (cc.sys.os === cc.sys.OS_IOS) {
                jsb.reflection.callStaticMethod('AppController', 'jsStopEvent:', event);
            } else if (cc.sys.os === cc.sys.OS_ANDROID) {
                jsb.reflection.callStaticMethod('org/cocos2dx/javascript/AppActivity', 'jsStopEvent', '(Ljava/lang/String;)V', event);
            }
        }
    }
});

module.exports = FMOD;