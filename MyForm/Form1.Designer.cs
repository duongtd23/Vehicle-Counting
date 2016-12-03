namespace MyForm
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
            this.txtInput = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.btnOutput = new System.Windows.Forms.Button();
            this.txtOutput = new System.Windows.Forms.TextBox();
            this.checkSaveOutput = new System.Windows.Forms.CheckBox();
            this.typeCounting = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btnStartStop = new System.Windows.Forms.Button();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.countCar = new System.Windows.Forms.Label();
            this.countMotor = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // txtInput
            // 
            this.txtInput.Location = new System.Drawing.Point(83, 4);
            this.txtInput.Name = "txtInput";
            this.txtInput.Size = new System.Drawing.Size(389, 20);
            this.txtInput.TabIndex = 0;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(2, 2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "Open";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // btnOutput
            // 
            this.btnOutput.Enabled = false;
            this.btnOutput.Location = new System.Drawing.Point(2, 123);
            this.btnOutput.Name = "btnOutput";
            this.btnOutput.Size = new System.Drawing.Size(75, 23);
            this.btnOutput.TabIndex = 2;
            this.btnOutput.Text = "Output";
            this.btnOutput.UseVisualStyleBackColor = true;
            this.btnOutput.Click += new System.EventHandler(this.button2_Click);
            // 
            // txtOutput
            // 
            this.txtOutput.Enabled = false;
            this.txtOutput.Location = new System.Drawing.Point(83, 126);
            this.txtOutput.Name = "txtOutput";
            this.txtOutput.Size = new System.Drawing.Size(389, 20);
            this.txtOutput.TabIndex = 3;
            // 
            // checkSaveOutput
            // 
            this.checkSaveOutput.AutoSize = true;
            this.checkSaveOutput.Enabled = false;
            this.checkSaveOutput.Location = new System.Drawing.Point(12, 100);
            this.checkSaveOutput.Name = "checkSaveOutput";
            this.checkSaveOutput.Size = new System.Drawing.Size(92, 17);
            this.checkSaveOutput.TabIndex = 4;
            this.checkSaveOutput.Text = "Save to video";
            this.checkSaveOutput.UseVisualStyleBackColor = true;
            this.checkSaveOutput.CheckedChanged += new System.EventHandler(this.checkSaveOutput_CheckedChanged);
            // 
            // typeCounting
            // 
            this.typeCounting.AllowDrop = true;
            this.typeCounting.FormattingEnabled = true;
            this.typeCounting.Items.AddRange(new object[] {
            "Top To Down",
            "Down To Top",
            "Combine"});
            this.typeCounting.Location = new System.Drawing.Point(12, 63);
            this.typeCounting.Name = "typeCounting";
            this.typeCounting.Size = new System.Drawing.Size(100, 21);
            this.typeCounting.TabIndex = 5;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 47);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(76, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Counting Type";
            // 
            // btnStartStop
            // 
            this.btnStartStop.Enabled = false;
            this.btnStartStop.Location = new System.Drawing.Point(15, 169);
            this.btnStartStop.Name = "btnStartStop";
            this.btnStartStop.Size = new System.Drawing.Size(61, 23);
            this.btnStartStop.TabIndex = 7;
            this.btnStartStop.Text = "Start";
            this.btnStartStop.UseVisualStyleBackColor = true;
            this.btnStartStop.Click += new System.EventHandler(this.btnStartStop_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label2.Location = new System.Drawing.Point(281, 169);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(42, 20);
            this.label2.TabIndex = 8;
            this.label2.Text = "Car:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label3.Location = new System.Drawing.Point(281, 198);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(60, 20);
            this.label3.TabIndex = 9;
            this.label3.Text = "Motor:";
            // 
            // label4
            // 
            this.countCar.AutoSize = true;
            this.countCar.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.countCar.Location = new System.Drawing.Point(353, 169);
            this.countCar.Name = "countCar";
            this.countCar.Size = new System.Drawing.Size(0, 20);
            this.countCar.TabIndex = 10;
            // 
            // countMotor
            // 
            this.countMotor.AutoSize = true;
            this.countMotor.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.countMotor.Location = new System.Drawing.Point(353, 197);
            this.countMotor.Name = "countMotor";
            this.countMotor.Size = new System.Drawing.Size(0, 20);
            this.countMotor.TabIndex = 11;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(481, 337);
            this.Controls.Add(this.countMotor);
            this.Controls.Add(this.countCar);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.btnStartStop);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.typeCounting);
            this.Controls.Add(this.checkSaveOutput);
            this.Controls.Add(this.txtOutput);
            this.Controls.Add(this.btnOutput);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.txtInput);
            this.Name = "Form1";
            this.Text = "Counting Vehicle";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtInput;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button btnOutput;
        private System.Windows.Forms.TextBox txtOutput;
        private System.Windows.Forms.CheckBox checkSaveOutput;
        private System.Windows.Forms.ComboBox typeCounting;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnStartStop;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label countCar;
        private System.Windows.Forms.Label countMotor;
    }
}

