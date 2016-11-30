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

namespace MyForm
{
    public partial class Form1 : Form
    {
        //đối tượng wrap từ C++ sang C#
        MyVehicleCountingWrapper myVehicleCountingWrapper;
        
        public Form1()
        {
            //init
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //click open - mở hộp thoại chọn file
            DialogResult result = openFileDialog1.ShowDialog(); // Show the dialog.
            if (result == DialogResult.OK) // Test result.
            {
                string filePath = openFileDialog1.FileName;
                System.Diagnostics.Debug.WriteLine(filePath);

                //khởi tạo đối tượng
                myVehicleCountingWrapper = new MyVehicleCountingWrapper(filePath);

                //bắt đầu đếm
                myVehicleCountingWrapper.functionMain("output/out.mp4");
            }
        }
    }
}
