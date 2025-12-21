#ifndef _DEVICE_H_
#define _DEVICE_H_

class InputDevice {
private:
	uint8_t _pin;
	uint32_t _activationMomentTime;
	bool _lastState = NOTACTIVE;
	bool _stableState = NOTACTIVE;

public:
	InputDevice(uint8_t pin) { _pin = pin; }
	
	void begin() {
		pinMode(_pin, INPUT_PULLDOWN);
	}
	
	bool isActive() {
		bool cur = digitalRead(_pin);
		if (cur != _lastState) {
			_lastState = cur;
			_activationMomentTime = millis();
		}
		if (millis() - _activationMomentTime >= 50) {
			if (_lastState != _stableState) {
				_stableState = _lastState;
				if (_stableState == ACTIVE) return true;
			}
		}
		return false;
	}
};

class OutputDevice {
	private:
	uint8_t _pin;
	uint8_t _st;
	uint32_t _timer;
	
	public:
	OutputDevice(uint8_t pin) { _pin = pin; }

	void activate() {
		digitalWrite(_pin, ON);
	}

	void disactivate() {
		digitalWrite(_pin, OFF);
	}

	void begin() {
		pinMode(_pin, OUTPUT);
		disactivate();
	}

	void resetDevice() {
		_st = 0;
	}

	bool activateForMiliseconds(uint32_t miliseconds) {
		switch (_st) {
		case 0:
			activate();
			_timer = millis();
			_st = 1;
			break;
		case 1:
			if (millis() - _timer >= miliseconds) {
				_st = 2;
			}
			break;
		case 2:
			disactivate();
			return true;
		}
		return false;
	}
};

#endif // _DEVICE_H_
