using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace lab_2
{
    public partial class Form1 : Form
    {
        Crypter crypter = new Crypter();

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string result = crypter.CryptString(textBox1.Text);
            textBox1.Text = result;
        }

    }
}
