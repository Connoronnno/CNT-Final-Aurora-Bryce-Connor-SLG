namespace undo
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
            this.textBox1 = new System.Windows.Forms.TextBox();
            this._process = new System.Windows.Forms.Button();
            this.UI_PicBox = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.UI_PicBox)).BeginInit();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(473, 13);
            this.textBox1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(581, 528);
            this.textBox1.TabIndex = 0;
            // 
            // _process
            // 
            this._process.Location = new System.Drawing.Point(12, 491);
            this._process.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this._process.Name = "_process";
            this._process.Size = new System.Drawing.Size(452, 50);
            this._process.TabIndex = 1;
            this._process.Text = "Process";
            this._process.UseVisualStyleBackColor = true;
            // 
            // UI_PicBox
            // 
            this.UI_PicBox.Location = new System.Drawing.Point(12, 13);
            this.UI_PicBox.Name = "UI_PicBox";
            this.UI_PicBox.Size = new System.Drawing.Size(454, 471);
            this.UI_PicBox.TabIndex = 2;
            this.UI_PicBox.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1067, 554);
            this.Controls.Add(this.UI_PicBox);
            this.Controls.Add(this._process);
            this.Controls.Add(this.textBox1);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.UI_PicBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button _process;
        private System.Windows.Forms.PictureBox UI_PicBox;
    }
}

