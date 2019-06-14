<title>PcaServo Component Dictionary</title>
# PcaServo Component Dictionary


## Command List

|Mnemonic|ID|Description|Arg Name|Arg Type|Comment
|---|---|---|---|---|---|
|PS_Set_Angle|0 (0x0)|Command to set angle of servo| | |
| | | |angle|F32|Commanded servo angle|
|PS_Set_Raw_PulseWidth|1 (0x1)|Command to set pulse width in milliseconds| | |
| | | |time|F32|Commanded pulse width time in milliseconds|
|PS_DIS|2 (0x2)|Disable servo board| | |
|PS_EN|3 (0x3)|Enable servo board| | |

## Telemetry Channel List

|Channel Name|ID|Type|Description|
|---|---|---|---|
|PS_Angle|0 (0x0)|F32|Commanded angle|
|PS_PulseWidth|2 (0x2)|F32|Raw pulse width|
|PS_Reg|3 (0x3)|U16|Register value|

## Event List

|Event Name|ID|Description|Arg Name|Arg Type|Arg Size|Description
|---|---|---|---|---|---|---|
|PS_AngleCmd|0 (0x0)|Angle commanded| | | | |
| | | |inst|U8||The motor instance|
| | | |angle|F32||The commanded angle|
| | | |pulse_width|F32||The commanded angle|
| | | |reg|U16||The register value|
|PS_PulseWidthCmd|0 (0x0)|Pulse width commanded| | | | |
| | | |inst|U8||The motor instance|
| | | |pulse_width|F32||The commanded angle|
| | | |reg|U16||The register value|
