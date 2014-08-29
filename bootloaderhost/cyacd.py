import crc16
import struct


class BootloaderRow(object):
    def __init__(self):
        self.array_id = None
        self.row_number = None
        self.data = None

    @classmethod
    def read(cls, data):
        self = cls()
        if data[0] != ':':
            raise ValueError("Bootloader rows must start with a colon")
        data = data[1:].decode('hex')
        self.array_id, self.row_number, data_length = struct.unpack('>BHH', data[:5])
        self.data = data[5:-1]
        if len(self.data) != data_length:
            raise ValueError("Row specified %d bytes of data, but got %d"
                             % (data_length, len(self.data)))
        (checksum,) = struct.unpack('B', data[-1])
        data_checksum = 0x100 - (sum(ord(x) for x in data[:-1]) & 0xFF)
        if checksum != data_checksum:
            raise ValueError("Computed checksum of %x, but expected %x" % (data_checksum, checksum))
        return self


class BootloaderData(object):
    def __init__(self):
        self.silicon_id = None
        self.silicon_rev = None
        self.checksum_type = None
        self.rows = []

    @classmethod
    def read(cls, f):
        header = f.readline().strip().decode('hex')
        if len(header) != 6:
            raise ValueError("Expected 12 byte header line first")
        self = cls()
        self.silicon_id, self.silicon_rev, self.checksum_type = struct.unpack('>LBB', header)
        self.rows = [BootloaderRow.read(line.strip()) for line in f]
        return self
