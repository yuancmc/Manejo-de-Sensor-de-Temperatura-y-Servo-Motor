using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Text.RegularExpressions;
using System.IO;

namespace Manejo_de_Sensor_de_Temperatura_y_Servo_Motor
{
    public partial class Form1 : Form
    {
        delegate void SetTextDelegate(string value);
        public SerialPort ArduinoPort
        {
            get;
        }
        public Form1()
        {
            InitializeComponent();
            ArduinoPort = new System.IO.Ports.SerialPort();
            ArduinoPort.PortName = "COM8";
            ArduinoPort.BaudRate = 9600;
            ArduinoPort.DataBits = 8;
            ArduinoPort.ReadTimeout = 1000;
            ArduinoPort.WriteTimeout = 1000;
            ArduinoPort.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);
            // ArduinoPort.Open();
        }

        private void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            string dato = ArduinoPort.ReadLine();
            EscribirText(dato);
        }

        private void EscribirText(string dato)
        {
            if (InvokeRequired)
                try
                {
                    Invoke(new SetTextDelegate(EscribirText), dato);
                }
                catch
                {
                    //Poner acción de aviso de error
                }
            else
                label4.Text = dato;
        }


        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            //button2.Enabled=true;
            //button2.Enabled=false;
            try
            {

                if (!ArduinoPort.IsOpen)
                    ArduinoPort.Open();
                if (int.TryParse(textBox1.Text, out int temperatureLimit))
                {

                    string limitString = temperatureLimit.ToString();
                    ArduinoPort.Write(limitString);
                }
                else
                {
                    MessageBox.Show("Ingresa un valor numérico válido en el textbox.");
                }

                label2.Text = "Conexión OK";
                label2.ForeColor = System.Drawing.Color.Lime;
            }
            catch
            {
                MessageBox.Show("Configure el puerto de comunicación correcto");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            button1.Enabled = true;
            button1.Enabled = false;
            if (ArduinoPort.IsOpen)
                ArduinoPort.Close();
            label2.Text = "Desconectado";
            label2.ForeColor = System.Drawing.Color.Red;
            label4.Text = "00,0";
        }

    }
}

