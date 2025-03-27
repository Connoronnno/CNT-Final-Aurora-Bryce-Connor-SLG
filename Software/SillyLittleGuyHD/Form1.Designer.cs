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
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.UI_LocationAmount_lbl = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.UI_StepsGroup_gbx = new System.Windows.Forms.GroupBox();
            this.UI_StepCount_lbl = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.UI_NextCycle_btn = new System.Windows.Forms.Button();
            this.UI_PrevCycle_btn = new System.Windows.Forms.Button();
            this.UI_PetPicture_pbx = new System.Windows.Forms.PictureBox();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.label3 = new System.Windows.Forms.Label();
            this.UI_Locations_lbx = new System.Windows.Forms.ListBox();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this._pEnBox = new System.Windows.Forms.CheckBox();
            this._uEnBox = new System.Windows.Forms.CheckBox();
            this._usernameBox = new System.Windows.Forms.TextBox();
            this._passBox = new System.Windows.Forms.TextBox();
            this.UI_SLG_btn = new System.Windows.Forms.Button();
            this.label11 = new System.Windows.Forms.Label();
            this.UI_GrabData_btn = new System.Windows.Forms.Button();
            this.UI_SendData_btn = new System.Windows.Forms.Button();
            this.UI_Map_gmap = new GMap.NET.WindowsForms.GMapControl();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.UI_StepsGroup_gbx.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UI_PetPicture_pbx)).BeginInit();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Interval = 500;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(7, 7);
            this.tabControl1.MinimumSize = new System.Drawing.Size(788, 438);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(788, 438);
            this.tabControl1.TabIndex = 5;
            // 
            // tabPage1
            // 
            this.tabPage1.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage1.Controls.Add(this.groupBox5);
            this.tabPage1.Controls.Add(this.groupBox4);
            this.tabPage1.Controls.Add(this.groupBox3);
            this.tabPage1.Controls.Add(this.groupBox2);
            this.tabPage1.Controls.Add(this.UI_StepsGroup_gbx);
            this.tabPage1.Controls.Add(this.groupBox1);
            this.tabPage1.Controls.Add(this.UI_PetPicture_pbx);
            this.tabPage1.Font = new System.Drawing.Font("Ink Free", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(780, 412);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Pet Menu";
            // 
            // groupBox5
            // 
            this.groupBox5.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox5.Controls.Add(this.label9);
            this.groupBox5.Controls.Add(this.label10);
            this.groupBox5.Location = new System.Drawing.Point(522, 242);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(237, 45);
            this.groupBox5.TabIndex = 11;
            this.groupBox5.TabStop = false;
            // 
            // label9
            // 
            this.label9.Font = new System.Drawing.Font("Ink Free", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(137, 15);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(94, 18);
            this.label9.TabIndex = 7;
            this.label9.Text = "N/A";
            this.label9.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Ink Free", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label10.Location = new System.Drawing.Point(17, 15);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(73, 20);
            this.label10.TabIndex = 6;
            this.label10.Text = "Evolution:";
            // 
            // groupBox4
            // 
            this.groupBox4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox4.Controls.Add(this.label7);
            this.groupBox4.Controls.Add(this.label8);
            this.groupBox4.Location = new System.Drawing.Point(522, 183);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(237, 45);
            this.groupBox4.TabIndex = 9;
            this.groupBox4.TabStop = false;
            // 
            // label7
            // 
            this.label7.Font = new System.Drawing.Font("Ink Free", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(137, 15);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(94, 18);
            this.label7.TabIndex = 7;
            this.label7.Text = "N/A";
            this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Ink Free", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(17, 15);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(115, 20);
            this.label8.TabIndex = 6;
            this.label8.Text = "Recent Emotion:";
            // 
            // groupBox3
            // 
            this.groupBox3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Location = new System.Drawing.Point(522, 124);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(237, 45);
            this.groupBox3.TabIndex = 10;
            this.groupBox3.TabStop = false;
            // 
            // label5
            // 
            this.label5.Font = new System.Drawing.Font("Ink Free", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(137, 15);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(94, 18);
            this.label5.TabIndex = 7;
            this.label5.Text = "???";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Ink Free", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(17, 15);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(122, 20);
            this.label6.TabIndex = 6;
            this.label6.Text = "Something Else?:";
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.UI_LocationAmount_lbl);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Location = new System.Drawing.Point(522, 65);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(237, 45);
            this.groupBox2.TabIndex = 9;
            this.groupBox2.TabStop = false;
            // 
            // UI_LocationAmount_lbl
            // 
            this.UI_LocationAmount_lbl.Font = new System.Drawing.Font("Ink Free", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.UI_LocationAmount_lbl.Location = new System.Drawing.Point(137, 15);
            this.UI_LocationAmount_lbl.Name = "UI_LocationAmount_lbl";
            this.UI_LocationAmount_lbl.Size = new System.Drawing.Size(94, 18);
            this.UI_LocationAmount_lbl.TabIndex = 7;
            this.UI_LocationAmount_lbl.Text = "N/A";
            this.UI_LocationAmount_lbl.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Ink Free", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(17, 15);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(124, 20);
            this.label4.TabIndex = 6;
            this.label4.Text = "Locations Visited:";
            // 
            // UI_StepsGroup_gbx
            // 
            this.UI_StepsGroup_gbx.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.UI_StepsGroup_gbx.Controls.Add(this.UI_StepCount_lbl);
            this.UI_StepsGroup_gbx.Controls.Add(this.label2);
            this.UI_StepsGroup_gbx.Location = new System.Drawing.Point(522, 6);
            this.UI_StepsGroup_gbx.Name = "UI_StepsGroup_gbx";
            this.UI_StepsGroup_gbx.Size = new System.Drawing.Size(237, 45);
            this.UI_StepsGroup_gbx.TabIndex = 8;
            this.UI_StepsGroup_gbx.TabStop = false;
            // 
            // UI_StepCount_lbl
            // 
            this.UI_StepCount_lbl.Font = new System.Drawing.Font("Ink Free", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.UI_StepCount_lbl.Location = new System.Drawing.Point(137, 15);
            this.UI_StepCount_lbl.Name = "UI_StepCount_lbl";
            this.UI_StepCount_lbl.Size = new System.Drawing.Size(94, 18);
            this.UI_StepCount_lbl.TabIndex = 7;
            this.UI_StepCount_lbl.Text = "N/A";
            this.UI_StepCount_lbl.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Ink Free", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(17, 15);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(97, 20);
            this.label2.TabIndex = 6;
            this.label2.Text = "Steps Taken:";
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
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
            this.UI_NextCycle_btn.Font = new System.Drawing.Font("Ink Free", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
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
            this.UI_PrevCycle_btn.Font = new System.Drawing.Font("Ink Free", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.UI_PrevCycle_btn.Location = new System.Drawing.Point(33, 57);
            this.UI_PrevCycle_btn.Name = "UI_PrevCycle_btn";
            this.UI_PrevCycle_btn.Size = new System.Drawing.Size(75, 23);
            this.UI_PrevCycle_btn.TabIndex = 2;
            this.UI_PrevCycle_btn.Text = "Previous";
            this.UI_PrevCycle_btn.UseVisualStyleBackColor = true;
            this.UI_PrevCycle_btn.Click += new System.EventHandler(this.UI_PrevCycle_btn_Click);
            // 
            // UI_PetPicture_pbx
            // 
            this.UI_PetPicture_pbx.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.UI_PetPicture_pbx.Location = new System.Drawing.Point(8, 6);
            this.UI_PetPicture_pbx.Name = "UI_PetPicture_pbx";
            this.UI_PetPicture_pbx.Size = new System.Drawing.Size(489, 400);
            this.UI_PetPicture_pbx.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.UI_PetPicture_pbx.TabIndex = 0;
            this.UI_PetPicture_pbx.TabStop = false;
            // 
            // tabPage2
            // 
            this.tabPage2.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage2.Controls.Add(this.UI_Map_gmap);
            this.tabPage2.Controls.Add(this.label3);
            this.tabPage2.Controls.Add(this.UI_Locations_lbx);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(780, 412);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "GPS Menu";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(93, 58);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(82, 20);
            this.label3.TabIndex = 8;
            this.label3.Text = "Locations:";
            // 
            // UI_Locations_lbx
            // 
            this.UI_Locations_lbx.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.UI_Locations_lbx.FormattingEnabled = true;
            this.UI_Locations_lbx.Items.AddRange(new object[] {
            "A",
            "B",
            "C",
            "D",
            "E",
            "G",
            "etc."});
            this.UI_Locations_lbx.Location = new System.Drawing.Point(19, 81);
            this.UI_Locations_lbx.Name = "UI_Locations_lbx";
            this.UI_Locations_lbx.Size = new System.Drawing.Size(236, 251);
            this.UI_Locations_lbx.TabIndex = 7;
            // 
            // tabPage3
            // 
            this.tabPage3.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage3.Controls.Add(this._pEnBox);
            this.tabPage3.Controls.Add(this._uEnBox);
            this.tabPage3.Controls.Add(this._usernameBox);
            this.tabPage3.Controls.Add(this._passBox);
            this.tabPage3.Controls.Add(this.UI_SLG_btn);
            this.tabPage3.Controls.Add(this.label11);
            this.tabPage3.Controls.Add(this.UI_GrabData_btn);
            this.tabPage3.Controls.Add(this.UI_SendData_btn);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(780, 412);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Save Menu";
            // 
            // _pEnBox
            // 
            this._pEnBox.AutoSize = true;
            this._pEnBox.Location = new System.Drawing.Point(450, 130);
            this._pEnBox.Name = "_pEnBox";
            this._pEnBox.Size = new System.Drawing.Size(107, 17);
            this._pEnBox.TabIndex = 7;
            this._pEnBox.Text = "update password";
            this._pEnBox.UseVisualStyleBackColor = true;
            // 
            // _uEnBox
            // 
            this._uEnBox.AutoSize = true;
            this._uEnBox.Location = new System.Drawing.Point(450, 104);
            this._uEnBox.Name = "_uEnBox";
            this._uEnBox.Size = new System.Drawing.Size(108, 17);
            this._uEnBox.TabIndex = 6;
            this._uEnBox.Text = "update username";
            this._uEnBox.UseVisualStyleBackColor = true;
            // 
            // _usernameBox
            // 
            this._usernameBox.Location = new System.Drawing.Point(344, 101);
            this._usernameBox.Name = "_usernameBox";
            this._usernameBox.Size = new System.Drawing.Size(100, 20);
            this._usernameBox.TabIndex = 5;
            // 
            // _passBox
            // 
            this._passBox.Location = new System.Drawing.Point(344, 127);
            this._passBox.Name = "_passBox";
            this._passBox.Size = new System.Drawing.Size(100, 20);
            this._passBox.TabIndex = 4;
            // 
            // UI_SLG_btn
            // 
            this.UI_SLG_btn.Location = new System.Drawing.Point(344, 185);
            this.UI_SLG_btn.Name = "UI_SLG_btn";
            this.UI_SLG_btn.Size = new System.Drawing.Size(93, 42);
            this.UI_SLG_btn.TabIndex = 3;
            this.UI_SLG_btn.Text = "Update SLG";
            this.UI_SLG_btn.UseVisualStyleBackColor = true;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label11.Location = new System.Drawing.Point(261, 18);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(259, 20);
            this.label11.TabIndex = 2;
            this.label11.Text = "Send and Recieve database values";
            this.label11.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // UI_GrabData_btn
            // 
            this.UI_GrabData_btn.Location = new System.Drawing.Point(398, 53);
            this.UI_GrabData_btn.Name = "UI_GrabData_btn";
            this.UI_GrabData_btn.Size = new System.Drawing.Size(93, 42);
            this.UI_GrabData_btn.TabIndex = 1;
            this.UI_GrabData_btn.Text = "Receive Data";
            this.UI_GrabData_btn.UseVisualStyleBackColor = true;
            // 
            // UI_SendData_btn
            // 
            this.UI_SendData_btn.Location = new System.Drawing.Point(299, 53);
            this.UI_SendData_btn.Name = "UI_SendData_btn";
            this.UI_SendData_btn.Size = new System.Drawing.Size(93, 42);
            this.UI_SendData_btn.TabIndex = 0;
            this.UI_SendData_btn.Text = "Send Save";
            this.UI_SendData_btn.UseVisualStyleBackColor = true;
            // 
            // UI_Map_gmap
            // 
            this.UI_Map_gmap.Bearing = 0F;
            this.UI_Map_gmap.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.UI_Map_gmap.CanDragMap = true;
            this.UI_Map_gmap.EmptyTileColor = System.Drawing.Color.Navy;
            this.UI_Map_gmap.GrayScaleMode = false;
            this.UI_Map_gmap.HelperLineOption = GMap.NET.WindowsForms.HelperLineOptions.DontShow;
            this.UI_Map_gmap.LevelsKeepInMemmory = 5;
            this.UI_Map_gmap.Location = new System.Drawing.Point(261, 6);
            this.UI_Map_gmap.MarkersEnabled = true;
            this.UI_Map_gmap.MaxZoom = 2;
            this.UI_Map_gmap.MinZoom = 2;
            this.UI_Map_gmap.MouseWheelZoomEnabled = true;
            this.UI_Map_gmap.MouseWheelZoomType = GMap.NET.MouseWheelZoomType.MousePositionAndCenter;
            this.UI_Map_gmap.Name = "UI_Map_gmap";
            this.UI_Map_gmap.NegativeMode = false;
            this.UI_Map_gmap.PolygonsEnabled = true;
            this.UI_Map_gmap.RetryLoadTile = 0;
            this.UI_Map_gmap.RoutesEnabled = true;
            this.UI_Map_gmap.ScaleMode = GMap.NET.WindowsForms.ScaleModes.Integer;
            this.UI_Map_gmap.SelectedAreaFillColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(65)))), ((int)(((byte)(105)))), ((int)(((byte)(225)))));
            this.UI_Map_gmap.ShowTileGridLines = false;
            this.UI_Map_gmap.Size = new System.Drawing.Size(513, 403);
            this.UI_Map_gmap.TabIndex = 9;
            this.UI_Map_gmap.Zoom = 0D;
            // 
            // PetMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.tabControl1);
            this.MinimumSize = new System.Drawing.Size(816, 489);
            this.Name = "PetMenu";
            this.Text = "Pet Display";
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.UI_StepsGroup_gbx.ResumeLayout(false);
            this.UI_StepsGroup_gbx.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.UI_PetPicture_pbx)).EndInit();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.PictureBox UI_PetPicture_pbx;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.ListBox UI_Locations_lbx;
        private System.Windows.Forms.Button UI_NextCycle_btn;
        private System.Windows.Forms.Button UI_PrevCycle_btn;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label UI_StepCount_lbl;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox UI_StepsGroup_gbx;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label UI_LocationAmount_lbl;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Button UI_GrabData_btn;
        private System.Windows.Forms.Button UI_SendData_btn;
        private System.Windows.Forms.Button UI_SLG_btn;
        private System.Windows.Forms.TextBox _usernameBox;
        private System.Windows.Forms.TextBox _passBox;
        private System.Windows.Forms.CheckBox _pEnBox;
        private System.Windows.Forms.CheckBox _uEnBox;
        private GMap.NET.WindowsForms.GMapControl UI_Map_gmap;
    }
}

