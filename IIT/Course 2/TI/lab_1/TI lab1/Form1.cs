using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace TI_lab1
{
    public partial class Form1 : Form
    {
        Monoalphabetic mo = new Monoalphabetic();
        string text = "";
        
        Stream myStream = null;
        string al = "etaoinsrhldcumfpgwybvkxjqz";

        public Form1()
        {
            InitializeComponent();
        }

        private void openBtn_Click(object sender, EventArgs e)
        {
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    if ((myStream = openFileDialog.OpenFile()) != null)
                    {
                        using (myStream)
                        {
                            text = System.IO.File.ReadAllText(openFileDialog.FileName, Encoding.Default);
                            textBox1.Text = text;
                            keyTextBox.Enabled = true;
                            scramblerBtn.Enabled = true;
                        }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
                }
            }
        }

        private void scramblerBtn_Click(object sender, EventArgs e)
        {
            decoderBar.Value = 0;
            decoderBar.Maximum = text.Length;
            textBox1.Text = "";
            for (int i = 0; i < text.Length; i++)
            {
                textBox1.Text += mo.Scrambler(text[i], Convert.ToInt32(keyTextBox.Text));
                decoderBar.Value += 1;
            }
            text = textBox1.Text;
            decoderBtn.Enabled = true;
            System.IO.File.WriteAllText(@"decoderText.txt", text);
            //MessageBox.Show(Convert.ToString(mo.Analyze(text)));
        }

        private void decoderBtn_Click(object sender, EventArgs e)
        {
            decoderBar.Value = 0;
            decoderBar.Maximum = text.Length;
            textBox1.Text = "";
            for (int i = 0; i < text.Length; i++)
            {
                textBox1.Text += mo.Decoder(text[i], Convert.ToInt32(keyTextBox.Text));
                decoderBar.Value += 1;
            }
            text = textBox1.Text;

        }

        private void statBtn_Click(object sender, EventArgs e)
        {
            bool flag = false;
            int ind = 0, key = 0;
            char c = mo.Analyze(text);
            decoderBar.Value = 0;
            decoderBar.Maximum = text.Length;
            while (!flag)
            {
                textBox1.Text = "";
                key = Math.Abs(al[ind] - c);
                for (int i = 0; i < text.Length; i++)
                {                    
                    textBox1.Text += mo.Decoder(text[i], key);
                    decoderBar.Value += 1;
                }
                var result = MessageBox.Show("Правильно?", "Подтверждение", MessageBoxButtons.OKCancel);
                if (result == System.Windows.Forms.DialogResult.OK)
                {
                    text = textBox1.Text;
                    MessageBox.Show("Ключ - " + key);
                    flag = true;
                    ind = 0;
                    break;
                }
                else
                {
                    if (ind < 27)
                    {
                        key = 0;
                        ind++;
                    }
                    else
                    {
                        flag = true;
                        ind = 0;
                        break;
                    }                    
                }
            }
        }
    }
}
