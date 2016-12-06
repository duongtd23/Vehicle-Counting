using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using CppWrapper;
using System.Threading;

namespace MyForm
{
    public partial class Form1 : Form
    {
        //đối tượng wrap từ C++ sang C#
        MyVehicleCountingWrapper myVehicleCountingWrapper;
        System.Windows.Forms.Timer myTimer;
        bool counting = false;
        Thread thread;
        
        public Form1()
        {
            //init
            InitializeComponent();
            typeCounting.SelectedIndex = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //click open - mở hộp thoại chọn file
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.InitialDirectory = "E:\\cpp projects\\NativeProj";
            openFileDialog1.RestoreDirectory = true;
            DialogResult result = openFileDialog1.ShowDialog(); // Show the dialog.
            if (result == DialogResult.OK) // Test result.
            {
                string filePath = openFileDialog1.FileName;
                System.Diagnostics.Debug.WriteLine(filePath);
                txtInput.Text = filePath;
                btnStartStop.Enabled = true;
                checkSaveOutput.Enabled = true;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //click open - mở hộp thoại chọn file
            //SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.InitialDirectory = "E:\\cpp projects\\NativeProj";
            saveFileDialog1.Filter = "avi Video|*.avi";
            saveFileDialog1.Title = "Save Video";
            saveFileDialog1.ShowDialog();

            // If the file name is not an empty string open it for saving.
            if (saveFileDialog1.FileName != "")
            {
                txtOutput.Text = saveFileDialog1.FileName;
            }
        }

        private void checkSaveOutput_CheckedChanged(object sender, EventArgs e)
        {
            if (!checkSaveOutput.Checked){
                btnOutput.Enabled = false;
                txtOutput.Enabled = false;
            }
            else
            {
                btnOutput.Enabled = true;
                txtOutput.Enabled = true;
            }
        }


        private void btnStartStop_Click(object sender, EventArgs e)
        {
            if (!counting)
            {
                counting = true;
                //khởi tạo đối tượng
                int type_count = typeCounting.SelectedIndex;
                System.Diagnostics.Debug.WriteLine("DUongthdg" + type_count);
                myVehicleCountingWrapper = new MyVehicleCountingWrapper(txtInput.Text,
                                        type_count);
                thread = new Thread(new ThreadStart(this.startCounting));
                thread.Start();

                //bắt đầu đếm
                btnStartStop.Text = "Stop";

                getNumberVehicle();
            }
            else
            {
                thread.Abort();
                myVehicleCountingWrapper.stopCounting();
                counting = false;
                myTimer.Stop();
                btnStartStop.Text = "Start";
            }
        }

        void startCounting()
        {
            
            myVehicleCountingWrapper.functionMain(txtOutput.Text, checkSaveOutput.Checked);
        }

        void getNumberVehicle() {
            myTimer = new System.Windows.Forms.Timer();
            myTimer.Interval = (50);
            myTimer.Tick += new EventHandler(MyTimer_Tick);
            myTimer.Start();
        }

        private void MyTimer_Tick(object sender, EventArgs e)
        {
            if (typeCounting.SelectedIndex == myVehicleCountingWrapper.COUNT_TOP_TO_DOWN)
            {
                int motorCount = myVehicleCountingWrapper.getMotorCountTTD();
                countMotor.Text = motorCount + "";

                int carCount = myVehicleCountingWrapper.getCarCountTTD();
                countCar.Text = carCount + "";
            }
            else if (typeCounting.SelectedIndex == myVehicleCountingWrapper.COUNT_DOWN_TO_TOP)
            {
                int motorCount = myVehicleCountingWrapper.getMotorCountDTT();
                countMotor.Text = motorCount + "";

                int carCount = myVehicleCountingWrapper.getCarCountDTT();
                countCar.Text = carCount + "";
            }
        }
    }
}
