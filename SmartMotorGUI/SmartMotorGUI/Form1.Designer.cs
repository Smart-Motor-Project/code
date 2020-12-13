
namespace SmartMotorGUI
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
            this.components = new System.ComponentModel.Container();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.startButton = new System.Windows.Forms.Button();
            this.stopButton = new System.Windows.Forms.Button();
            this.radiusTextbox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.qTextbox = new System.Windows.Forms.TextBox();
            this.statusTextbox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.infuseRadioBtn = new System.Windows.Forms.RadioButton();
            this.extractRadiotBtn = new System.Windows.Forms.RadioButton();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.SuspendLayout();
            // 
            // serialPort1
            // 
            this.serialPort1.PortName = "COM4";
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived_1);
            // 
            // startButton
            // 
            this.startButton.Location = new System.Drawing.Point(57, 155);
            this.startButton.Name = "startButton";
            this.startButton.Size = new System.Drawing.Size(75, 23);
            this.startButton.TabIndex = 0;
            this.startButton.Text = "Start";
            this.startButton.UseVisualStyleBackColor = true;
            this.startButton.Click += new System.EventHandler(this.startButton_Click);
            // 
            // stopButton
            // 
            this.stopButton.Location = new System.Drawing.Point(168, 155);
            this.stopButton.Name = "stopButton";
            this.stopButton.Size = new System.Drawing.Size(75, 23);
            this.stopButton.TabIndex = 1;
            this.stopButton.Text = "Stop";
            this.stopButton.UseVisualStyleBackColor = true;
            this.stopButton.Click += new System.EventHandler(this.stopButton_Click);
            // 
            // radiusTextbox
            // 
            this.radiusTextbox.Location = new System.Drawing.Point(41, 81);
            this.radiusTextbox.Name = "radiusTextbox";
            this.radiusTextbox.Size = new System.Drawing.Size(100, 20);
            this.radiusTextbox.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(150, 84);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(103, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Syringe Radius (mm)";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(150, 50);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(138, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Volumetric Flow Rate (uL/s)";
            // 
            // qTextbox
            // 
            this.qTextbox.Location = new System.Drawing.Point(41, 47);
            this.qTextbox.Name = "qTextbox";
            this.qTextbox.Size = new System.Drawing.Size(100, 20);
            this.qTextbox.TabIndex = 5;
            // 
            // statusTextbox
            // 
            this.statusTextbox.BackColor = System.Drawing.Color.Silver;
            this.statusTextbox.ForeColor = System.Drawing.Color.Black;
            this.statusTextbox.Location = new System.Drawing.Point(97, 210);
            this.statusTextbox.Name = "statusTextbox";
            this.statusTextbox.Size = new System.Drawing.Size(100, 20);
            this.statusTextbox.TabIndex = 6;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(54, 213);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(37, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Status";
            // 
            // infuseRadioBtn
            // 
            this.infuseRadioBtn.AutoSize = true;
            this.infuseRadioBtn.Location = new System.Drawing.Point(341, 50);
            this.infuseRadioBtn.Name = "infuseRadioBtn";
            this.infuseRadioBtn.Size = new System.Drawing.Size(54, 17);
            this.infuseRadioBtn.TabIndex = 8;
            this.infuseRadioBtn.TabStop = true;
            this.infuseRadioBtn.Text = "Infuse";
            this.infuseRadioBtn.UseVisualStyleBackColor = true;
            // 
            // extractRadiotBtn
            // 
            this.extractRadiotBtn.AutoSize = true;
            this.extractRadiotBtn.Location = new System.Drawing.Point(341, 74);
            this.extractRadiotBtn.Name = "extractRadiotBtn";
            this.extractRadiotBtn.Size = new System.Drawing.Size(58, 17);
            this.extractRadiotBtn.TabIndex = 9;
            this.extractRadiotBtn.TabStop = true;
            this.extractRadiotBtn.Text = "Extract";
            this.extractRadiotBtn.UseVisualStyleBackColor = true;
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(219, 207);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(100, 23);
            this.progressBar1.TabIndex = 10;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(656, 385);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.extractRadiotBtn);
            this.Controls.Add(this.infuseRadioBtn);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.statusTextbox);
            this.Controls.Add(this.qTextbox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.radiusTextbox);
            this.Controls.Add(this.stopButton);
            this.Controls.Add(this.startButton);
            this.Name = "Form1";
            this.Text = "Smart Motor GUI";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Button startButton;
        private System.Windows.Forms.Button stopButton;
        private System.Windows.Forms.TextBox radiusTextbox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox qTextbox;
        private System.Windows.Forms.TextBox statusTextbox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.RadioButton infuseRadioBtn;
        private System.Windows.Forms.RadioButton extractRadiotBtn;
        private System.Windows.Forms.ProgressBar progressBar1;
    }
}

