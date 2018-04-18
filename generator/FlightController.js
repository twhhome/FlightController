'use strict';
goog.provide('Blockly.Arduino.Flightcontroller');
goog.require('Blockly.Arduino');


function bound100(inp)
{
    if (inp > 100){return 100}
    if (typeof inp == 'string'){return 0}
    return inp
    
}

Blockly.Arduino.FlightController_startprogram = function() {
    Blockly.Arduino.definitions_['define1_FlightController'] = '#include "Aircraft.h"';
    Blockly.Arduino.definitions_['define2_FlightController_Vehicle'] = 'Aircraft* '+'Vehicle;\n';
    Blockly.Arduino.definitions_['define3_Interrupt'] = 'boolean first_run = true;\n';
    var code='if(first_run == true)\n{\nVehicle = new Aircraft;\nProgramInit();\nwhile(!Vehicle->ProgramShouldRun());\nVehicle->Init();\nVehicle->Connect();\nfirst_run = false;\nVehicle->StartProgram();\n}\n';
    return code;
};

Blockly.Arduino.FlightController_takeoff = function() {
    var code='Vehicle->TakeOff();\n';
    return code;
};

Blockly.Arduino.FlightController_land = function() {
    var code='Vehicle->Land();\n';
    return code;
};

Blockly.Arduino.FlightController_endprogram = function() {
    var code='Vehicle->RepeatProgram();\n';
    return code;
};

Blockly.Arduino.FlightController_forward = function() {
    var msec = Blockly.Arduino.valueToCode(this, 'TIME', Blockly.Arduino.ORDER_ATOMIC);
    var dropdown_time_type = this.getFieldValue('TIME_TYPE');
    
    if (dropdown_time_type=='SEC'){msec = msec * 1000;}
    
    var speed = Blockly.Arduino.valueToCode(this, 'SPEED', Blockly.Arduino.ORDER_ATOMIC);
    
    var code='Vehicle->Forward('+msec+', '+bound100(speed)+');\n';
    return code;
};

Blockly.Arduino.FlightController_backward = function() {
    var msec = Blockly.Arduino.valueToCode(this, 'TIME', Blockly.Arduino.ORDER_ATOMIC);
    var dropdown_time_type = this.getFieldValue('TIME_TYPE');
    
    if (dropdown_time_type=='SEC'){msec = msec * 1000;}
    
    var speed = Blockly.Arduino.valueToCode(this, 'SPEED', Blockly.Arduino.ORDER_ATOMIC);
    
    var code='Vehicle->Backward('+msec+', '+bound100(speed)+');\n';
    return code;
};

Blockly.Arduino.FlightController_goup = function() {
    var msec = Blockly.Arduino.valueToCode(this, 'TIME', Blockly.Arduino.ORDER_ATOMIC);
    var dropdown_time_type = this.getFieldValue('TIME_TYPE');
    
    if (dropdown_time_type=='SEC'){msec = msec * 1000;}
    
    var speed = Blockly.Arduino.valueToCode(this, 'SPEED', Blockly.Arduino.ORDER_ATOMIC);
    
    var code='Vehicle->GoUp('+msec+', '+bound100(speed)+');\n';
    return code;
};

Blockly.Arduino.FlightController_godown = function() {
    var msec = Blockly.Arduino.valueToCode(this, 'TIME', Blockly.Arduino.ORDER_ATOMIC);
    var dropdown_time_type = this.getFieldValue('TIME_TYPE');
    
    if (dropdown_time_type=='SEC'){msec = msec * 1000;}
    
    var speed = Blockly.Arduino.valueToCode(this, 'SPEED', Blockly.Arduino.ORDER_ATOMIC);
    
    var code='Vehicle->GoDown('+msec+', '+bound100(speed)+');\n';
    return code;
};

Blockly.Arduino.FlightController_goleft = function() {
    var msec = Blockly.Arduino.valueToCode(this, 'TIME', Blockly.Arduino.ORDER_ATOMIC);
    var dropdown_time_type = this.getFieldValue('TIME_TYPE');
    
    if (dropdown_time_type=='SEC'){msec = msec * 1000;}
    
    var speed = Blockly.Arduino.valueToCode(this, 'SPEED', Blockly.Arduino.ORDER_ATOMIC);
    
    var code='Vehicle->GoLeft('+msec+', '+bound100(speed)+');\n';
    return code;
};

Blockly.Arduino.FlightController_goright = function() {
    var msec = Blockly.Arduino.valueToCode(this, 'TIME', Blockly.Arduino.ORDER_ATOMIC);
    var dropdown_time_type = this.getFieldValue('TIME_TYPE');
    
    if (dropdown_time_type=='SEC'){msec = msec * 1000;}
    
    var speed = Blockly.Arduino.valueToCode(this, 'SPEED', Blockly.Arduino.ORDER_ATOMIC);
    
    var code='Vehicle->GoRight('+msec+', '+bound100(speed)+');\n';
    return code;
};

Blockly.Arduino.FlightController_turnleft = function() {
    var msec = Blockly.Arduino.valueToCode(this, 'TIME', Blockly.Arduino.ORDER_ATOMIC);
    var dropdown_time_type = this.getFieldValue('TIME_TYPE');
    
    if (dropdown_time_type=='SEC'){msec = msec * 1000;}
    
    var speed = Blockly.Arduino.valueToCode(this, 'SPEED', Blockly.Arduino.ORDER_ATOMIC);
    
    var code='Vehicle->TurnLeft('+msec+', '+bound100(speed)+');\n';
    return code;
};

Blockly.Arduino.FlightController_turnright = function() {
    var msec = Blockly.Arduino.valueToCode(this, 'TIME', Blockly.Arduino.ORDER_ATOMIC);
    var dropdown_time_type = this.getFieldValue('TIME_TYPE');
    
    if (dropdown_time_type=='SEC'){msec = msec * 1000;}
    
    var speed = Blockly.Arduino.valueToCode(this, 'SPEED', Blockly.Arduino.ORDER_ATOMIC);
    
    var code='Vehicle->TurnRight('+msec+', '+bound100(speed)+');\n';
    return code;
};

Blockly.Arduino.FlightController_hover = function() {
    var msec = Blockly.Arduino.valueToCode(this, 'TIME', Blockly.Arduino.ORDER_ATOMIC);
    var dropdown_time_type = this.getFieldValue('TIME_TYPE');
    
    if (dropdown_time_type=='SEC'){msec = msec * 1000;}
    
    var code='Vehicle->Hover('+msec+');\n';
    return code;
};

Blockly.Arduino.FlightController_flip = function() {
    var dirc = this.getFieldValue('FLIP_TYPE');
    
    switch(dirc)
    {
        case 1: var code='Vehicle->RollLeft();\n'; break;
        case 2: var code='Vehicle->RollBackward();\n'; break;
        case 3: var code='Vehicle->RollRight();\n'; break;
        default: var code = 'Vehicle->RollForward();\n';
    }
    
    return code;
};
