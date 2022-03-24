// See https://aka.ms/new-console-template for more information
using System;
using System.Runtime.InteropServices;

Charon.Client.Test.Main();

namespace Charon.Client
{
    public delegate void CharonCallback(Error errorCode, ref Byte[] buffer, UInt32 length);

    public enum Error
    {
        OK,
        NotResponding,
        NegativeRespone,
        Pending,
        Busy,
        NotSupported,
        ComSpeedNotAdjusted,
        Unexpected,
        MessageTooLong
    }

    public enum TimerRates
    {
        SlowTimer = 0x01,
        MediumTimer = 0x02,
        FastTimer = 0x03,
    }

    public class ComInterface
    {
        public delegate int sendFunc(ref Byte[] data, UInt32 length);
        public delegate int receiveFunc(ref Byte[] data, UInt32 length);
        public delegate bool setSpeedFunc(UInt32 speed);
        public sendFunc send;
        public receiveFunc receive;
        public setSpeedFunc setSpeed;
        public bool speedIsAdjustable;
    }
    public class TimerInterface
    {
        public delegate UInt32 getTimeFunc();
        public delegate Int64 diffTimeFunc(UInt32 start, UInt32 stop);
        public getTimeFunc getTime;
        public diffTimeFunc diffTime;
    }
    public class SecurityInterface
    {
        public delegate Byte[] encryptFunc(ref Byte[] data, UInt32 length);
        public delegate Byte[] decryptFunc(ref Byte[] data, UInt32 length);
    }
    public struct MemoryDefinition
    {
        public Byte[] Address;
        public Byte[] Size;
        public byte AddressLength;
        public byte SizeLength;
    }
    public struct DataDefinition
    {
        public UInt16 DID;
        public byte firstBytePosition;
        public byte memorySize;
    }
    public static class Client
    {
        [DllImport("Test_Charon_Dll.dll", EntryPoint = "UDS_Client_Init")]
        public static extern void Init(ComInterface com, TimerInterface timer, SecurityInterface security, Byte[] rxBuffer, UInt32 rxBufferLength);
        [DllImport("Test_Charon_Dll.dll", EntryPoint = "UDS_Client_Task")]
        public static extern Error Task();
    }
    public static class DataTransmitter
    {
        [DllImport("Test_Charon_Dll.dll", EntryPoint = "UDS_DT_readDataByIdentifier")]
        public static extern bool readDataByIdentifier(ref UInt16[] dataIdentifier, byte length, CharonCallback callback);
        [DllImport("Test_Charon_Dll.dll", EntryPoint = "UDS_DT_readMemoryByAddress")]
        public static extern bool readMemoryByAddress(MemoryDefinition sourceMemory, CharonCallback callback);
        [DllImport("Test_Charon_Dll.dll", EntryPoint = "UDS_DT_readScalingDataByIdentifier")]
        public static extern bool readScalingDataByIdentifier(UInt16 dataIdentifier, CharonCallback callback);
        [DllImport("Test_Charon_Dll.dll", EntryPoint = "UDS_DT_ReadDataByPeriodicIdentifier")]
        public static extern bool readDataByPeriodicIdentifier(TimerRates transmissionMode, ref Byte[] periodicDataIdentifiers, byte periodicDataIdLength, CharonCallback callback, CharonCallback response_callback);
        [DllImport("Test_Charon_Dll.dll", EntryPoint = "UDS_DT_stopDataByPeriodicIdentifier")]
        public static extern bool stopDataByPeriodicIdentifier(ref Byte[] periodicDataIdentifiers, byte periodicDtaIdsLength, CharonCallback callback);
        [DllImport("Test_Charon_Dll.dll", EntryPoint = "UDS_DT_dynamicallyDefineDataIdentifierByDID")]
        public static extern bool dynamicallyDefineDataIdentifierByDID(UInt16 definedDataIdentifier, [In] DataDefinition SourceDataDefinition, byte SourceDataDefinitionsLength, CharonCallback callback);
        [DllImport("Test_Charon_Dll.dll", EntryPoint = "UDS_DT_dynamicallyDefineDataIdentifierByMemoryDefinition")]
        public static extern bool dynamicallyDefineDataIdentifierByMemoryDefinition(UInt16 definedDataIdentifier, [In] MemoryDefinition SourceMemoryDefinitions, byte SourceMemoryLength, CharonCallback callback);
        [DllImport("Test_Charon_Dll.dll", EntryPoint = "UDS_DT_clearDynamicallyDefineDataIdentifier")]
        public static extern bool clearDynamicallyDefinedDataIdentifier(UInt16 definedDataIdentifier, CharonCallback callback);
        [DllImport("Test_Charon_Dll.dll", EntryPoint = "UDS_DT_writeDataByIdentifier")]
        public static extern bool writeDataByIdentifier(UInt16 dataIdentifier, byte[] writeBuffer, byte bufferLength, CharonCallback callback);
        [DllImport("Test_Charon_Dll.dll", EntryPoint = "UDS_DT_writeMemoryByAddress")]
        public static extern bool writeMemoryByAddress(MemoryDefinition targetMemory, byte[] writeBuffer, byte bufferLength, CharonCallback callback);
    }

    public class Test
    {
        static byte[] rxBuffer;
        static ComInterface Com = new ComInterface();
        static TimerInterface Timer = new TimerInterface();
        static Dictionary<uint, DateTime> actualTime = new Dictionary<uint, DateTime>();
        static byte[] buf = new byte[4096];
        public static int Main()
        {
            
            ComInterface.sendFunc send = new ComInterface.sendFunc(Send);
            ComInterface.receiveFunc receive = new ComInterface.receiveFunc(Receive);
            ComInterface.setSpeedFunc speed = new ComInterface.setSpeedFunc(SetSpeed);
            Com.send = send;
            Com.receive = receive;
            Com.setSpeed = speed;
            Com.speedIsAdjustable = false;
            Timer.getTime = new TimerInterface.getTimeFunc(GetTime);
            Timer.diffTime = new TimerInterface.diffTimeFunc(DiffTime);
            Client.Init(Com, Timer, null, buf, 4096);
            return 0;
        }

        public static int Send(ref byte[] data, uint length)
        {
            Console.WriteLine("Sent: %s", data);
            return (int)length;
        }

        public static int Receive(ref byte[] data, uint length)
        {
            Console.WriteLine("Going to receive: %s", rxBuffer);
            rxBuffer.CopyTo(data, 0);
            return rxBuffer.Length;
        }

        public static bool SetSpeed(uint speed) => true;

        public static uint GetTime()
        {
            DateTime now = DateTime.Now;
            actualTime.Add((uint)now.Ticks, now);
            return (uint)now.Ticks;
        }

        public static long DiffTime(uint start, uint stop)
        {
            if(actualTime.ContainsKey(start) && actualTime.ContainsKey(stop))
            {
                return actualTime[stop].Ticks - actualTime[start].Ticks;
            }
            else
            {
                long startOverflow = UInt32.MaxValue - start + stop;
                long startToStop = stop - start;
                return Math.Abs(startOverflow) < Math.Abs(startToStop) ? startOverflow : startToStop;
            }
        }
    }

}
