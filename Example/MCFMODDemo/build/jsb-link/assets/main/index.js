window.__require = function c(t, e, s) {
function n(i, o) {
if (!e[i]) {
if (!t[i]) {
var r = i.split("/");
r = r[r.length - 1];
if (!t[r]) {
var l = "function" == typeof __require && __require;
if (!o && l) return l(r, !0);
if (a) return a(r, !0);
throw new Error("Cannot find module '" + i + "'");
}
i = r;
}
var u = e[i] = {
exports: {}
};
t[i][0].call(u.exports, function(c) {
return n(t[i][1][c] || c);
}, u, u.exports, c, t, e, s);
}
return e[i].exports;
}
for (var a = "function" == typeof __require && __require, i = 0; i < s.length; i++) n(s[i]);
return n;
}({
main: [ function(c, t) {
"use strict";
cc._RF.push(t, "e22a5UlHvdKqbt30vd8GrHn", "main");
var e = c("mostar_fmod");
cc.Class({
extends: cc.Component,
properties: {},
start: function() {
this.paused = !1;
e.load();
},
playZhucheng: function() {
e.playMusic(e.zhucheng);
},
pauseZhucheng: function() {
e.pauseMusic(e.zhucheng);
},
resumeZhucheng: function() {
e.resumeMusic(e.zhucheng);
},
stopZhucheng: function() {
e.stopMusic(e.zhucheng);
},
playSenlin: function() {
e.playMusic(e.senlin);
},
pauseSenlin: function() {
e.pauseMusic(e.senlin);
},
resumeSenlin: function() {
e.resumeMusic(e.senlin);
},
stopSenlin: function() {
e.stopMusic(e.senlin);
},
playeffect: function() {
e.playEffect(e.bianda);
},
stopeffect: function() {
e.stopEffect(e.bianda);
}
});
cc._RF.pop();
}, {
mostar_fmod: "mostar_fmod"
} ],
mostar_fmod: [ function(c, t) {
"use strict";
cc._RF.push(t, "3c2d7hDw9VGV4dLiFpIuKLS", "mostar_fmod");
var e = cc.Class({
statics: {
test: "event:/Music/Level 03",
zhucheng: {
event: "event:/MUSIC/music_switch",
paramer: "music switch",
value: 0
},
senlin: {
event: "event:/MUSIC/music_switch",
paramer: "music switch",
value: 2
},
bianda: "event:/SFX/jinzhandongzuo/sfx_1jinzhan_bianda",
load: function() {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsLoadBank") : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsLoadBank", "()V");
},
playMusic: function(c) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsPlayMusicEvent:andParamer:andValue:", c.event, c.paramer, c.value) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsPlayMusicEvent", "(Ljava/lang/String;Ljava/lang/String;F)V", c.event, c.paramer, c.value);
},
pauseMusic: function(c) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsPauseMusicEvent:andParamer:andValue:", c.event, c.paramer, c.value) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsPauseMusicEvent", "(Ljava/lang/String;Ljava/lang/String;F)V", c.event, c.paramer, c.value);
},
resumeMusic: function(c) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsResumeMusicEvent:andParamer:andValue:", c.event, c.paramer, c.value) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsResumeMusicEvent", "(Ljava/lang/String;Ljava/lang/String;F)V", c.event, c.paramer, c.value);
},
stopMusic: function(c) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsStopMusicEvent:andParamer:andValue:", c.event, c.paramer, c.value) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsStopMusicEvent", "(Ljava/lang/String;Ljava/lang/String;F)V", c.event, c.paramer, c.value);
},
playEffect: function(c) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsPlayEffectEvent:", c) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsPlayEffectEvent", "(Ljava/lang/String;)V", c);
},
stopEffect: function(c) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsStopEffectEvent:", c) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsStopEffectEvent", "(Ljava/lang/String;)V", c);
}
}
});
t.exports = e;
cc._RF.pop();
}, {} ]
}, {}, [ "main", "mostar_fmod" ]);