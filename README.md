# PvFaultDetection
______________________________________________________________________________________________________________________________
# Introduction:
The multiplication of photovoltaic panels number poses a problem for the maintenance teams. Indeed, for the fields which are in distant zones or little inhabited it is difficult to move for the control and the maintenance.
So, our IoT application is the proposed solution, it simplifies and makes more efficient maintenance operations and moving to the fields to verify their state. In fact, we will detect and identify the failure to avoid the movement of teams in the event of irreparable breakdowns.
_______________________________________________________________________________________________________________________________
# Description:
this project contains two parts:
- the first part is the collection and sending of data by Arduino boards
- the second is the processing of this data to detect and identify the failure
# Data collection
In order to determine the state of each photo-voltaic panel, we have to measure the current flowing in the circuit, the voltage at the terminals of each panel and the intensity of sunshine arriving on the field. For this reason, we thought to use the Arduino micro-controller for its simplicity to use and its large platform which contains all the libraries that we need for these measurements.
In fact, these measurements will be taken by the following sensors:
- the light sensor GY-30.
- the ACS712 current sensor.

And for the voltage, it will be measured by the analog inputs of the Arduino board following a set of operations allowing the adaptation of the potential difference arrieved between the GND port and these inputs. the circuit of these operations is detailed in the proteus project 
The recovered data will be sent by a CC1101 module.
