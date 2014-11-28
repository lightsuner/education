using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TI_lab1
{
    class Monoalphabetic
    {
        string AL = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string al = "abcdefghijklmnopqrstuvwxyz";
        
        public char Scrambler(char c, int key)
        {
            for (int i = 0; i < al.Length; i++)
            {
                if (char.IsLetter(c))
                {
                    if (char.IsUpper(c))
                    {

                        if (c.Equals(AL[i]))
                        {
                            c = AL[(i + key) % 26];
                            return c;
                        }
                    }
                    else
                        if (c.Equals(al[i]))
                        {
                            c = al[(i + key) % 26];
                            return c;
                        }
                }
                else
                    return c;
            }
            return ' ';
            
        }

        public char Decoder(char c, int key)
        {
            for (int i = 0; i < al.Length; i++)
            {
                if (char.IsLetter(c))
                {
                    if (char.IsUpper(c))
                    {
                        if (c.Equals(AL[i]))
                        {
                            c = AL[(i + 26 - key) % 26];
                            return c;
                        }
                    }
                    else
                        if (c.Equals(al[i]))
                        {
                            c = al[(i + 26 - key) % 26];
                            return c;
                        }
                }
                else return c;
            }
            return ' ';
        }

        public char Analyze(string text)
        {
            int max = 0, index = 0, current=0;
            char s=' ';
            for (int i = 0; i < text.Length; i++)
            {
                for (int j = i; j < text.Length - i; j++)
                {
                    if (text[i] != ' ')
                        if (char.ToLower(text[i]) == char.ToLower(text[j]))
                        {
                            current += 1;
                            index = i;
                        }
                }
                if (current > max)
                {
                    max = current;
                    s = text[index];
                }
                current = 0;
            }
            return s;
        }
    }
}
