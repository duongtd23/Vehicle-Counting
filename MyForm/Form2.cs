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
    public partial class Form2 : Form
    {
        //đối tượng wrap từ C++ sang C#
        MyVehicleCountingWrapper myVehicleCountingWrapper;

        public Form2()
        {
            InitializeComponent();
        }

        private void axWindowsMediaPlayer1_Enter(object sender, EventArgs e)
        {

        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog open = new OpenFileDialog();
            open.Title = "Open";
            open.Filter = "All Files|*.*";
            try
            {
                if (open.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {


                    //khởi tạo đối tượng
                    myVehicleCountingWrapper = new MyVehicleCountingWrapper(open.FileName, myVehicleCountingWrapper.COUNT_DOWN_TO_TOP);

                    //bắt đầu đếm
                    myVehicleCountingWrapper.functionMain();
                    axWindowsMediaPlayer1.URL = (open.FileName);
                }
            }
            catch (ArgumentException ex)
            {
                MessageBox.Show(ex.Message.ToString(), "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message.ToString(), "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
