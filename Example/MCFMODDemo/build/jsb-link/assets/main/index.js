window.__require = function c(s, e, t) {
function n(i, o) {
if (!e[i]) {
if (!s[i]) {
var r = i.split("/");
r = r[r.length - 1];
if (!s[r]) {
var u = "function" == typeof __require && __require;
if (!o && u) return u(r, !0);
if (a) return a(r, !0);
throw new Error("Cannot find module '" + i + "'");
}
i = r;
}
var l = e[i] = {
exports: {}
};
s[i][0].call(l.exports, function(c) {
return n(s[i][1][c] || c);
}, l, l.exports, c, s, e, t);
}
return e[i].exports;
}
for (var a = "function" == typeof __require && __require, i = 0; i < t.length; i++) n(t[i]);
return n;
}({
main: [ function(c, s) {
"use strict";
cc._RF.push(s, "e22a5UlHvdKqbt30vd8GrHn", "main");
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
}
});
cc._RF.pop();
}, {
mostar_fmod: "mostar_fmod"
} ],
mostar_fmod: [ function(c, s) {
"use strict";
cc._RF.push(s, "3c2d7hDw9VGV4dLiFpIuKLS", "mostar_fmod");
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
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsPlayMusicEvent:andParamer:andValue:", c.event, c.paramer, c.value) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsPlayMusicEvent", "(Ljava/lang/String;)V", c);
},
pauseMusic: function(c) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsPauseMusicEvent:andParamer:andValue:", c.event, c.paramer, c.value) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsPauseMusicEvent", "(Ljava/lang/String;)V", c);
},
resumeMusic: function(c) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsResumeMusicEvent:andParamer:andValue:", c.event, c.paramer, c.value) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsResumeMusicEvent", "(Ljava/lang/String;)V", c);
},
stopMusic: function(c) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsStopMusicEvent:andParamer:andValue:", c.event, c.paramer, c.value) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsStopMusicEvent", "(Ljava/lang/String;)V", c);
},
playEffect: function(c) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsPlayEffectEvent:", c) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsPlayEffectEvent", "(Ljava/lang/String;)V", c);
}
}
});
s.exports = e;
cc._RF.pop();
}, {} ]
}, {}, [ "main", "mostar_fmod" ]);