#!/usr/bin/env python
import argparse
import logging
import re
import serial
import time


logging.basicConfig(level=logging.DEBUG)


parser = argparse.ArgumentParser(description="Test and calibrate the Re:load Pro")
parser.add_argument('--baud', metavar='BAUD', type=int, help="Baud rate", default=115200)
parser.add_argument('port', metavar='PORT', help="Serial port")
parser.add_argument('--current', '-i', metavar='I', type=int, help="Calibration current in microamps")
parser.add_argument('--voltage', '-v', metavar='V', type=int, help="Calibration voltage in microvolts")


class QuitError(Exception): pass

def expect(value, expectation):
	if value != expectation:
		logging.error("Expected %r, got %r", expectation, value)
		raise QuitError()


def read_adcs(ser):
	ser.write("read\n")
	line = ser.readline()
	match = re.search("^read (-?\d+) (-?\d+)\r\n$", line)
	if not match:
		logging.error("Expected read response, got %r", line)
		raise QuitError()
	return map(int, match.groups())


def basic_test(args, ser):
	volts, amps = read_adcs(ser)
	if abs(volts) > 10000:
		logging.error("Offset voltage %d is greater than 10mV", volts)
		raise QuitError()
	if abs(amps) > 10000:
		logging.error("Offset current %d is greater than 10mA", amps)
		raise QuitError()
	logging.info("Communications okay")
	logging.info("Offsets okay")


def calibrate_offset(args, ser):
	ser.write("set 0\n")
	expect(ser.readline(), "set 0\r\n")
	ser.write("cal o\n")
	expect(ser.readline(), "ok\r\n")
	logging.info("Calibrated offsets")


def calibrate_voltage(args, ser):
	raw_input("Connect voltage source and press enter to continue.")
	volts, amps = read_adcs(ser)
	if args.voltage * 0.8 < volts < args.voltage * 1.2:
		logging.error("Initial voltage more than 20% out: %d", volts)
		raise QuitError()
	ser.write("cal v %d\n" % (args.voltage,))
	expect(ser.readline(), "ok\r\n")
	logging.info("Calibrated voltage")


def calibrate_current(args, ser):
	ser.write("set 6000\n")
	expect(ser.readline(), "set 6000\r\n")
	time.sleep(2.0)
	volts, amps = read_adcs(ser)
	if args.current * 0.8 < amps < args.current * 1.2:
		logging.error("Initial current more than 20% out: %d", amps)
		raise QuitError()
	ser.write("cal i %d\n" % (args.current,))
	expect(ser.readline(), "ok\r\n")
	logging.info("Calibrated current")


def calibrate_dacs(args, ser):
	ser.write("cal d %d\n" % (args.current * 0.8,))
	expect(ser.readline(), "ok\r\n")
	time.sleep(2.0)
	logging.info("Calibrated DACs")


def main(args):
	ser = serial.Serial(args.port, args.baud, timeout=1)
	
	basic_test(args, ser)
	calibrate_offset(args, ser)
	calibrate_voltage(args, ser)
	calibrate_current(args, ser)
	calibrate_dacs(args, ser)
	logging.info("Done!")


if __name__ == '__main__':
	try:
		main(parser.parse_args())
	except QuitError:
		pass
