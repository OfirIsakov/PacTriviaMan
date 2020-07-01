using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Text;

/// <summary>Sent from client to server.</summary>
public enum PacketsCodes
{
    signupCode = 1,
    loginCode = 2,
    errorCode = 3,
    createRoomCode = 4,
    getRoomsCode = 5,
    getPlayersInRoomCode = 6,
    joinRoomCode = 7,
    getStatisticsCode = 8,
    logoutCode = 9,
    closeRoomCode = 10,
    startGameCode = 11,
    getRoomStateCode = 12,
    leaveRoomCode = 13,
    LeaveGameCode = 14,
    GetQuestionCode = 15,
    SubmitAnswerCode = 16,
    GetGameResultCode = 17
}

public class Packet : IDisposable
{
    private List<byte> buffer;
    private byte[] readableBuffer;
    private int readPos;

    /// <summary>Creates a new empty packet (without an ID).</summary>
    public Packet()
    {
        buffer = new List<byte>(); // Intitialize buffer
        readPos = 0; // Set readPos to 0
    }

    /// <summary>Creates a packet from which data can be read. Used for receiving.</summary>
    /// <param name="_data">The bytes to add to the packet.</param>
    public Packet(int code, string json)
    {
        buffer = new List<byte>(); // Intitialize buffer
        readPos = 0; // Set readPos to 0


        Write(Convert.ToByte(Convert.ToChar(code)));
        Write(json.Length);
        Write(json);
    }
    public Packet(int code)
    {
        buffer = new List<byte>(); // Intitialize buffer
        readPos = 0; // Set readPos to 0

        Write(Convert.ToByte(Convert.ToChar(code)));
    }
    public Packet(byte[] _data)
    {
        buffer = new List<byte>(); // Intitialize buffer
        readPos = 0; // Set readPos to 0

        SetBytes(_data);
    }

    #region Functions
    /// <summary>Sets the packet's content and prepares it to be read.</summary>
    /// <param name="_data">The bytes to add to the packet.</param>
    public void SetBytes(byte[] _data)
    {
        Write(_data);
        readableBuffer = buffer.ToArray();
    }
    /// <summary>Gets the packet's content in array form.</summary>
    public byte[] ToArray()
    {
        readableBuffer = buffer.ToArray();
        return readableBuffer;
    }

    /// <summary>Gets the length of the packet's content.</summary>
    public int Length()
    {
        return buffer.Count; // Return the length of buffer
    }

    /// <summary>Gets the length of the unread data contained in the packet.</summary>
    public int UnreadLength()
    {
        return Length() - readPos; // Return the remaining length (unread)
    }

    #endregion

    #region Write Data
    /// <summary>Adds a byte to the packet.</summary>
    /// <param name="_value">The byte to add.</param>
    public void Write(byte _value)
    {
        buffer.Add(_value);
    }
    /// <summary>Adds an array of bytes to the packet.</summary>
    /// <param name="_value">The byte array to add.</param>
    public void Write(byte[] _value)
    {
        buffer.AddRange(_value);
    }
    /// <summary>Adds an int to the packet.</summary>
    /// <param name="_value">The int to add.</param>
    public void Write(int _value)
    {
        byte[] bytes = BitConverter.GetBytes(_value);
        Array.Reverse(bytes);
        buffer.AddRange(bytes);
    }
    /// <summary>Adds a string to the packet.</summary>
    /// <param name="_value">The string to add.</param>
    public void Write(string _value)
    {
        buffer.AddRange(Encoding.ASCII.GetBytes(_value)); // Add the string itself
    }
    #endregion

    #region Read Data
    /// <summary>Reads a byte from the packet.</summary>
    /// <param name="_moveReadPos">Whether or not to move the buffer's read position.</param>
    public byte ReadByte(bool _moveReadPos = true)
    {
        if (buffer.Count > readPos)
        {
            // If there are unread bytes
            byte _value = readableBuffer[readPos]; // Get the byte at readPos' position
            if (_moveReadPos)
            {
                // If _moveReadPos is true
                readPos += 1; // Increase readPos by 1
            }
            return _value; // Return the byte
        }
        else
        {
            throw new Exception("Could not read value of type 'byte'!");
        }
    }

    /// <summary>Reads an array of bytes from the packet.</summary>
    /// <param name="_length">The length of the byte array.</param>
    /// <param name="_moveReadPos">Whether or not to move the buffer's read position.</param>
    public byte[] ReadBytes(int _length, bool _moveReadPos = true)
    {
        if (buffer.Count > readPos)
        {
            // If there are unread bytes
            byte[] _value = buffer.GetRange(readPos, _length).ToArray(); // Get the bytes at readPos' position with a range of _length
            if (_moveReadPos)
            {
                // If _moveReadPos is true
                readPos += _length; // Increase readPos by _length
            }
            return _value; // Return the bytes
        }
        else
        {
            throw new Exception("Could not read value of type 'byte[]'!");
        }
    }
    public int ReadCode(bool _moveReadPos = true)
    {
        return (int)readableBuffer[0]; // Convert the FIRST byte to an int
    }
    public int ReadLength(bool _moveReadPos = true)
    {
        byte[] length = new byte[4];
        length[0] = readableBuffer[1];
        length[1] = readableBuffer[2];
        length[2] = readableBuffer[3];
        length[3] = readableBuffer[4];
        Array.Reverse(length);
        return BitConverter.ToInt32(length, 0); // Convert bytes 2-5 to an int
    }

    /// <summary>Reads a string from the packet.</summary>
    /// <param name="_moveReadPos">Whether or not to move the buffer's read position.</param>
    public string ReadJson()
    {
        int _length = ReadLength(); // Get the length of the string
        Debug.Log(_length);
        string _value = Encoding.ASCII.GetString(readableBuffer, 5, _length); // Convert the bytes to a string
        return _value; // Return the string
    }
    #endregion

    private bool disposed = false;

    protected virtual void Dispose(bool _disposing)
    {
        if (!disposed)
        {
            if (_disposing)
            {
                buffer = null;
                readableBuffer = null;
                readPos = 0;
            }

            disposed = true;
        }
    }

    public void Dispose()
    {
        Dispose(true);
        GC.SuppressFinalize(this);
    }
}
