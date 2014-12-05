using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace lab_2
{
    class Crypter
    {
        byte[] gamma = {1,1,1,0,0,1,0,1,1};

        public string CryptString(string inputString)
        {
            int gammaSize = gamma.Length;
            byte[] stringBites = StringToBites(inputString);
            int stringBitesLength = stringBites.Length;
            byte[] xoredStringBites = new byte[stringBitesLength];

            for (int i = 0; i < stringBitesLength; i++)
            {
                xoredStringBites[i] = (byte)(stringBites[i] ^ (gamma[i % gammaSize]));
            }

            return BitesToString(xoredStringBites);
        }

        public byte[] CryptBytes(byte[] inputBytes)
        {
            int gammaSize = gamma.Length;
            byte[] stringBites = BytesToBites(inputBytes);
            int stringBitesLength = stringBites.Length;
            byte[] xoredStringBites = new byte[stringBitesLength];

            for (int i = 0; i < stringBitesLength; i++)
            {
                xoredStringBites[i] = (byte)(stringBites[i] ^ (gamma[i % gammaSize]));
            }

            return BitesToBytes(xoredStringBites);
        }

        protected string BitesToString(byte[] bites)
        {
            List<Byte> byteList = new List<Byte>();
            string bitesString = string.Join("", bites.Select(b => b.ToString()).ToArray());

            for (int i = 0; i < bitesString.Length; i += EncodingBytesSupport())
            {
                byteList.Add(Convert.ToByte(bitesString.Substring(i, EncodingBytesSupport()), 2));
            }

            return ClassEncoding().GetString(byteList.ToArray());
        }


        protected byte[] BitesToBytes(byte[] bites)
        {
            List<Byte> byteList = new List<Byte>();
            string bitesString = string.Join("", bites.Select(b => b.ToString()).ToArray());

            for (int i = 0; i < bitesString.Length; i += EncodingBytesSupport())
            {
                byteList.Add(Convert.ToByte(bitesString.Substring(i, EncodingBytesSupport()), 2));
            }

            return byteList.ToArray();
        }

        protected byte[] BytesToBites(byte[] inputBytes)
        {
            int bitesCount = inputBytes.Length * EncodingBytesSupport();
            byte[] stringToBites = new byte[bitesCount];
            int i = 0;

            foreach (char c in inputBytes)
            {
                foreach (char subC in Convert.ToString(c, 2).PadLeft(EncodingBytesSupport(), '0'))
                {
                    stringToBites[i] = (byte)Char.GetNumericValue(subC);
                    i++;
                }
            }
            return stringToBites;
        }

        protected byte[] StringToBites(string inputString)
        {
            int bitesCount = ClassEncoding().GetByteCount(inputString) * EncodingBytesSupport();
            byte[] stringToBites = new byte[bitesCount];
            int i = 0;

            foreach (char c in inputString.ToCharArray())
            {
                foreach (char subC in Convert.ToString(c, 2).PadLeft(EncodingBytesSupport(), '0')) 
                {
                    stringToBites[i] = (byte)Char.GetNumericValue(subC);
                    i++;
                }
            }
            return stringToBites;
        }

        protected int EncodingBytesSupport()
        {
            return 8;
        }

        protected Encoding ClassEncoding()
        {
            return System.Text.Encoding.ASCII;
        }
    }
}
