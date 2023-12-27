// Learn cc.Class:
//  - https://docs.cocos.com/creator/manual/en/scripting/class.html
// Learn Attribute:
//  - https://docs.cocos.com/creator/manual/en/scripting/reference/attributes.html
// Learn life-cycle callbacks:
//  - https://docs.cocos.com/creator/manual/en/scripting/life-cycle-callbacks.html

let FMOD = require('mostar_fmod');

cc.Class({
    extends: cc.Component,

    properties: {
    },

    // LIFE-CYCLE CALLBACKS:

    // onLoad () {},

    start () {
        this.paused = false;
        FMOD.load();
    },

    playZhucheng() {
        console.log("cocos play");
        FMOD.playMusic(FMOD.zhucheng);
    },
    pauseZhucheng() {
        FMOD.pauseMusic(FMOD.zhucheng);
    },
    resumeZhucheng() {
        FMOD.resumeMusic(FMOD.zhucheng);
    },
    stopZhucheng() {
        FMOD.stopMusic(FMOD.zhucheng)
    },

    playSenlin() {
        FMOD.playMusic(FMOD.senlin);
    },
    pauseSenlin() {
        FMOD.pauseMusic(FMOD.senlin);
    },
    resumeSenlin() {
        FMOD.resumeMusic(FMOD.senlin);
    },
    stopSenlin() {
        FMOD.stopMusic(FMOD.senlin);
    },

    playeffect() {
      FMOD.playEffect(FMOD.amb);
    },
    stopeffect() {
        FMOD.stopEffect(FMOD.amb);
    },

    // update (dt) {},
});
