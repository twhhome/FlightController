'use strict';
goog.provide('Blockly.Blocks.Flightcontroller');
goog.require('Blockly.Blocks');

var TIME_TYPES = [["秒","SEC"],["毫秒","MSEC"]];
var FLIP_TYPES = [["前",0],["左",1],["后",2],["右",3]]
var HUE = 188;

Blockly.Blocks.FlightController_startprogram={
  init: function() {
    this.appendDummyInput("")
        .appendField('开始程序');
	//this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(HUE);
    this.setTooltip('初始化无人机控制器及将控制器与无人机连接');
    this.setHelpUrl('');
  }
};

Blockly.Blocks.FlightController_takeoff={
  init: function() {
    this.appendDummyInput("")
        .appendField('起飞')
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(HUE);
    this.setTooltip('命令无人机起飞');
    this.setHelpUrl('');
  }
};

Blockly.Blocks.FlightController_land={
  init: function() {
    this.appendDummyInput("")
        .appendField('降落')
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(HUE);
    this.setTooltip('命令无人机降落');
    this.setHelpUrl('');
  }
};

Blockly.Blocks.FlightController_endprogram={
  init: function() {
    this.appendDummyInput("")
        .appendField('结束程序')
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(HUE);
    this.setTooltip('结束程序');
    this.setHelpUrl('');
  }
};

Blockly.Blocks.FlightController_forward={
  init: function() {
    this.appendDummyInput("")
        .appendField('向前飞行');
	this.appendValueInput("TIME")
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(TIME_TYPES), "TIME_TYPE");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true);
    this.setColour(HUE);
    this.setTooltip('命令无人机向前飞行');
    this.setHelpUrl('');
  }
};

Blockly.Blocks.FlightController_backward={
  init: function() {
    this.appendDummyInput("")
        .appendField('向后飞行');
	this.appendValueInput("TIME")
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(TIME_TYPES), "TIME_TYPE");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true);
    this.setColour(HUE);
    this.setTooltip('命令无人机向后飞行');
    this.setHelpUrl('');
  }
};

Blockly.Blocks.FlightController_goup={
  init: function() {
    this.appendDummyInput("")
        .appendField('上升');
	this.appendValueInput("TIME")
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(TIME_TYPES), "TIME_TYPE");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true);
    this.setColour(HUE);
    this.setTooltip('命令无人机上升高度');
    this.setHelpUrl('');
  }
};

Blockly.Blocks.FlightController_godown={
  init: function() {
    this.appendDummyInput("")
        .appendField('下降');
	this.appendValueInput("TIME")
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(TIME_TYPES), "TIME_TYPE");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true);
    this.setColour(HUE);
    this.setTooltip('命令无人机下降高度');
    this.setHelpUrl('');
  }
};

Blockly.Blocks.FlightController_goleft={
  init: function() {
    this.appendDummyInput("")
        .appendField('向左飞行');
	this.appendValueInput("TIME")
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(TIME_TYPES), "TIME_TYPE");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true);
    this.setColour(HUE);
    this.setTooltip('命令无人机向左飞行');
    this.setHelpUrl('');
  }
};

Blockly.Blocks.FlightController_goright={
  init: function() {
    this.appendDummyInput("")
        .appendField('向右飞行');
	this.appendValueInput("TIME")
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(TIME_TYPES), "TIME_TYPE");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true);
    this.setColour(HUE);
    this.setTooltip('命令无人机向右飞行');
    this.setHelpUrl('');
  }
};

Blockly.Blocks.FlightController_turnleft={
  init: function() {
    this.appendDummyInput("")
        .appendField('向左转向');
	this.appendValueInput("TIME")
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(TIME_TYPES), "TIME_TYPE");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true);
    this.setColour(HUE);
    this.setTooltip('命令无人机向左转向');
    this.setHelpUrl('');
  }
};

Blockly.Blocks.FlightController_turnright={
  init: function() {
    this.appendDummyInput("")
        .appendField('向右转向');
	this.appendValueInput("TIME")
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(TIME_TYPES), "TIME_TYPE");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true);
    this.setColour(HUE);
    this.setTooltip('命令无人机向右转向');
    this.setHelpUrl('');
  }
};

Blockly.Blocks.FlightController_hover={
  init: function() {
    this.appendDummyInput("")
        .appendField('原地悬停');
	this.appendValueInput("TIME")
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(TIME_TYPES), "TIME_TYPE");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true);
    this.setColour(HUE);
    this.setTooltip('命令无人机原地悬停一段时间');
    this.setHelpUrl('');
  }
};


Blockly.Blocks.FlightController_flip={
  init: function() {
    this.appendDummyInput("")
        .appendField('向');
	this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(FLIP_TYPES), "FLIP_TYPE");
	this.appendDummyInput("")
        .appendField('翻筋斗');
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true);
    this.setColour(HUE);
    this.setTooltip('命令无人机朝某个方向翻筋斗');
    this.setHelpUrl('');
  }
};
