// Read Device Settings
let torqueAtRest = $prop('Settings.torqueAtRest') * 0.001;
let torqueAtMaximumAcceleration = $prop('Settings.torqueAtMaximumAcceleration') * 0.001;
let torqueAtMaximumDeceleration = $prop('Settings.torqueAtMaximumDeceleration') * 0.001;

const surgeMaximum = 25;
const surgeMinimum = 15;
const swayMaximum = 25;

// Calculate Surge
let surgeRaw = Math.max(surgeMinimum * -1, Math.min(surgeMaximum, $prop('AccelerationSurge')));
let surgePercent = (surgeRaw >= 0)
    ? (surgeRaw / surgeMaximum)
    : (surgeRaw / surgeMinimum);
let surgeTorque = torqueAtRest + ((surgePercent >= 0)
	? (surgePercent * (torqueAtMaximumDeceleration - torqueAtRest))
    : (Math.abs(surgePercent) * (torqueAtMaximumAcceleration - torqueAtRest))
);

// Calculate Sway
let swayRaw = Math.max(swayMaximum * -1, Math.min(swayMaximum, $prop('AccelerationSway')));
let swayPercent = (swayRaw / swayMaximum);

// Calculate Torque
let leftTorque = Math.min(1, surgeTorque + Math.max(swayPercent, 0));
let rightTorque = Math.min(1, surgeTorque - Math.min(swayPercent, 0));

// Return Telemetry
return '|' + [
	Math.round(leftTorque * 1000),
    Math.round(rightTorque * 1000),
    Math.round(torqueAtRest * 1000),
].join(',');
