using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SmartMotorGUI
{
    public partial class Form1 : Form
    {
        public delegate void d1(string indata);
        //private static int counter;

        public Form1()
        {
            InitializeComponent();
            serialPort1.Open();

        }

        private void startButton_Click(object sender, EventArgs e)
        {
            //Send command to the arduino to start
            if (infuseRadioBtn.Checked)
            {
                string start_vals = "A" + qTextbox.Text + "R" + radiusTextbox.Text;
                serialPort1.Write(start_vals);
            }

            if (extractRadiotBtn.Checked)
            {
                string start_vals = "B" + qTextbox.Text + "R" + radiusTextbox.Text;
                serialPort1.Write(start_vals);
            }

        }

        private void stopButton_Click(object sender, EventArgs e)
        {
            serialPort1.Write("C");
        }

        //stores data for processing
        private void serialPort1_DataReceived_1(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            string indata = serialPort1.ReadLine(); //readline function of serial port 1 and stores it
            d1 writeit = new d1(Write2Form);
            Invoke(writeit, indata);
        }

        public void Write2Form(string indata)
        {
            // this functino handles data sent from the Arduino
            char run_char;
            run_char = indata[0];
            statusTextbox.Text = Convert.ToString(indata[0]);

            switch (run_char)
            {
                case 'a':
                    statusTextbox.Text = "Running";
                    //statusTextbox.Text = Convert.ToString(run_char);      //used for testing
                    progressBar1.Value = 100;
                    break;

                case 'b':
                    statusTextbox.Text = "Stopped";
                    //statusTextbox.Text = Convert.ToString(run_char);      //used for testing
                    progressBar1.Value = 0;
                    break;

            }

        }
    }
}
