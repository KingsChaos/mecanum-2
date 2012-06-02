#ifndef DIGITALPUBLISHER_H
#define DIGITALPUBLISHER_H

#include "FiniteStateMachine.h"

#include <stdint.h> // for uint8_t

/**
 * DigitalPublisher will broadcast the state of a digital pin over serial at
 * the given frequency (approximately).
 *
 * Message:
 * uint8 length (4)
 * uint8 ID (FSM_DIGITALPUBLISHER)
 * uint8 pin
 * uint8 state (0 or 1)
 */
class DigitalPublisher : public FiniteStateMachine
{
public:
	DigitalPublisher(uint8_t pin, unsigned long delay /* ms */);

	virtual ~DigitalPublisher() { }

	virtual void Step();

	virtual unsigned long Delay() const { return m_delay; }

	/**
	 * By specifying a long delay, this publisher becomes a service. When a
	 * message is sent to it (and the message's pin matches its pin), it will
	 * emit the digital value to the serial port on command.
	 */
	virtual bool Message(const char* msg, unsigned char length);

private:
	uint8_t m_pin;
	unsigned long m_delay; // ms
};

#endif // DIGITALPUBLISHER_H