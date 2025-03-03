namespace SillyLittleGuyHD
{
    partial class PetMenu
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
            this.components = new System.ComponentModel.Container();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.UI_NextCycle_btn = new System.Windows.Forms.Button();
            this.UI_PrevCycle_btn = new System.Windows.Forms.Button();
            this.UI_PetStats_lbx = new System.Windows.Forms.ListBox();
            this.UI_PetPicture_pbx = new System.Windows.Forms.PictureBox();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.UI_Map_pbx = new System.Windows.Forms.PictureBox();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UI_PetPicture_pbx)).BeginInit();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UI_Map_pbx)).BeginInit();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Interval = 500;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(788, 438);
            this.tabControl1.TabIndex = 5;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.groupBox1);
            this.tabPage1.Controls.Add(this.UI_PetStats_lbx);
            this.tabPage1.Controls.Add(this.UI_PetPicture_pbx);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(780, 412);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Pet Menu";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.UI_NextCycle_btn);
            this.groupBox1.Controls.Add(this.UI_PrevCycle_btn);
            this.groupBox1.Location = new System.Drawing.Point(522, 293);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(236, 99);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Papyrus", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(33, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(170, 23);
            this.label1.TabIndex = 4;
            this.label1.Text = "Image Selection";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // UI_NextCycle_btn
            // 
            this.UI_NextCycle_btn.Location = new System.Drawing.Point(128, 57);
            this.UI_NextCycle_btn.Name = "UI_NextCycle_btn";
            this.UI_NextCycle_btn.Size = new System.Drawing.Size(75, 23);
            this.UI_NextCycle_btn.TabIndex = 3;
            this.UI_NextCycle_btn.Text = "Next";
            this.UI_NextCycle_btn.UseVisualStyleBackColor = true;
            this.UI_NextCycle_btn.Click += new System.EventHandler(this.UI_NextCycle_btn_Click);
            // 
            // UI_PrevCycle_btn
            // 
            this.UI_PrevCycle_btn.Location = new System.Drawing.Point(33, 57);
            this.UI_PrevCycle_btn.Name = "UI_PrevCycle_btn";
            this.UI_PrevCycle_btn.Size = new System.Drawing.Size(75, 23);
            this.UI_PrevCycle_btn.TabIndex = 2;
            this.UI_PrevCycle_btn.Text = "Previous";
            this.UI_PrevCycle_btn.UseVisualStyleBackColor = true;
            this.UI_PrevCycle_btn.Click += new System.EventHandler(this.UI_PrevCycle_btn_Click);
            // 
            // UI_PetStats_lbx
            // 
            this.UI_PetStats_lbx.FormattingEnabled = true;
            this.UI_PetStats_lbx.Location = new System.Drawing.Point(522, 16);
            this.UI_PetStats_lbx.Name = "UI_PetStats_lbx";
            this.UI_PetStats_lbx.Size = new System.Drawing.Size(236, 251);
            this.UI_PetStats_lbx.TabIndex = 1;
            // 
            // UI_PetPicture_pbx
            // 
            this.UI_PetPicture_pbx.Location = new System.Drawing.Point(8, 6);
            this.UI_PetPicture_pbx.Name = "UI_PetPicture_pbx";
            this.UI_PetPicture_pbx.Size = new System.Drawing.Size(489, 400);
            this.UI_PetPicture_pbx.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.UI_PetPicture_pbx.TabIndex = 0;
            this.UI_PetPicture_pbx.TabStop = false;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.UI_Map_pbx);
            this.tabPage2.Controls.Add(this.listBox1);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(780, 412);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "GPS Menu";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // UI_Map_pbx
            // 
            this.UI_Map_pbx.Location = new System.Drawing.Point(285, 6);
            this.UI_Map_pbx.Name = "UI_Map_pbx";
            this.UI_Map_pbx.Size = new System.Drawing.Size(489, 400);
            this.UI_Map_pbx.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.UI_Map_pbx.TabIndex = 6;
            this.UI_Map_pbx.TabStop = false;
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(19, 81);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(236, 251);
            this.listBox1.TabIndex = 7;
            // 
            // tabPage3
            // 
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(780, 412);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Save Menu";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // PetMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.tabControl1);
            this.Name = "PetMenu";
            this.Text = "Pet Display";
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.UI_PetPicture_pbx)).EndInit();
            this.tabPage2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.UI_Map_pbx)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.PictureBox UI_PetPicture_pbx;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.ListBox UI_PetStats_lbx;
        private System.Windows.Forms.PictureBox UI_Map_pbx;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Button UI_NextCycle_btn;
        private System.Windows.Forms.Button UI_PrevCycle_btn;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
    }
}

