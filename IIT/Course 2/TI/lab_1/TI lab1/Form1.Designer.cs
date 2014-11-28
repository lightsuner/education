namespace TI_lab1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.openBtn = new System.Windows.Forms.Button();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.scramblerBtn = new System.Windows.Forms.Button();
            this.decoderBtn = new System.Windows.Forms.Button();
            this.keyTextBox = new System.Windows.Forms.TextBox();
            this.key = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.statBtn = new System.Windows.Forms.Button();
            this.decoderBar = new System.Windows.Forms.ProgressBar();
            this.SuspendLayout();
            // 
            // openBtn
            // 
            this.openBtn.Location = new System.Drawing.Point(13, 13);
            this.openBtn.Name = "openBtn";
            this.openBtn.Size = new System.Drawing.Size(75, 23);
            this.openBtn.TabIndex = 0;
            this.openBtn.Text = "Открыть файл";
            this.openBtn.UseVisualStyleBackColor = true;
            this.openBtn.Click += new System.EventHandler(this.openBtn_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "text";
            this.openFileDialog.Filter = "Текстовые файлы|*.txt";
            // 
            // scramblerBtn
            // 
            this.scramblerBtn.Location = new System.Drawing.Point(212, 15);
            this.scramblerBtn.Name = "scramblerBtn";
            this.scramblerBtn.Size = new System.Drawing.Size(98, 23);
            this.scramblerBtn.TabIndex = 1;
            this.scramblerBtn.Text = "Зашифровать";
            this.scramblerBtn.UseVisualStyleBackColor = true;
            this.scramblerBtn.Click += new System.EventHandler(this.scramblerBtn_Click);
            // 
            // decoderBtn
            // 
            this.decoderBtn.Location = new System.Drawing.Point(316, 15);
            this.decoderBtn.Name = "decoderBtn";
            this.decoderBtn.Size = new System.Drawing.Size(102, 23);
            this.decoderBtn.TabIndex = 2;
            this.decoderBtn.Text = "Расшифровать";
            this.decoderBtn.UseVisualStyleBackColor = true;
            this.decoderBtn.Click += new System.EventHandler(this.decoderBtn_Click);
            // 
            // keyTextBox
            // 
            this.keyTextBox.Location = new System.Drawing.Point(130, 15);
            this.keyTextBox.Name = "keyTextBox";
            this.keyTextBox.Size = new System.Drawing.Size(76, 20);
            this.keyTextBox.TabIndex = 3;
            // 
            // key
            // 
            this.key.AutoSize = true;
            this.key.Location = new System.Drawing.Point(94, 18);
            this.key.Name = "key";
            this.key.Size = new System.Drawing.Size(36, 13);
            this.key.TabIndex = 4;
            this.key.Text = "Ключ:";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(12, 70);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(405, 387);
            this.textBox1.TabIndex = 5;
            // 
            // statBtn
            // 
            this.statBtn.Location = new System.Drawing.Point(316, 41);
            this.statBtn.Name = "statBtn";
            this.statBtn.Size = new System.Drawing.Size(101, 23);
            this.statBtn.TabIndex = 6;
            this.statBtn.Text = "Стат. анализ";
            this.statBtn.UseVisualStyleBackColor = true;
            this.statBtn.Click += new System.EventHandler(this.statBtn_Click);
            // 
            // decoderBar
            // 
            this.decoderBar.Location = new System.Drawing.Point(210, 463);
            this.decoderBar.Name = "decoderBar";
            this.decoderBar.Size = new System.Drawing.Size(207, 23);
            this.decoderBar.TabIndex = 7;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(433, 492);
            this.Controls.Add(this.decoderBar);
            this.Controls.Add(this.statBtn);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.key);
            this.Controls.Add(this.keyTextBox);
            this.Controls.Add(this.decoderBtn);
            this.Controls.Add(this.scramblerBtn);
            this.Controls.Add(this.openBtn);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ТИ Лаб.1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button openBtn;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.Button scramblerBtn;
        private System.Windows.Forms.Button decoderBtn;
        private System.Windows.Forms.TextBox keyTextBox;
        private System.Windows.Forms.Label key;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button statBtn;
        private System.Windows.Forms.ProgressBar decoderBar;

    }
}

