using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace lab_2
{
    public partial class Form1 : Form
    {
        Crypter crypter = new Crypter();
        Stream myStream = null;
        string text = "";

        public Form1()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    if ((myStream = openFileDialog1.OpenFile()) != null)
                    {
                        using (myStream)
                        {
                            //text = System.IO.File.ReadAllText(openFileDialog1.FileName);
                            byte[] tmp = System.IO.File.ReadAllBytes(openFileDialog1.FileName);

                            string path = Path.GetDirectoryName(openFileDialog1.FileName);
                            string fileName = Path.GetFileNameWithoutExtension(openFileDialog1.FileName);
                            string ext = Path.GetExtension(openFileDialog1.FileName);
                            string newFileName = fileName + "_mod" + ext;
                            label2.Text = newFileName;
                            System.IO.File.WriteAllBytes(path +"\\"+ newFileName, crypter.CryptBytes(tmp));
                        }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
                }
            }
            //string result = crypter.CryptString(textBox1.Text);

        }

    }
}
