using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;

namespace CS
{
    public partial class MainForm : Form
    {
        PictureBox ui_pbImage2;

        public MainForm()
        {
            InitializeComponent();

            ui_pbImage.Image = Image.FromFile("image.png");
            
            ui_pbImage2 = new PictureBox();
            ui_pbImage2.Parent = this;
            ui_pbImage2.Location = new Point(13, 98);
            ui_pbImage2.Size = new Size(100, 50);
            ui_pbImage2.Image = Image.FromFile("image.png");
            ui_pbImage2.MouseDown += new System.Windows.Forms.MouseEventHandler(this.ui_pbImage_MouseDown);
            MessageBox.Show("ㅊㅋ");
        }

        public void SetLevel(int nLevel)
        {
            if (nLevel == 1)
            {
                
            }
            else
            {

            }
        }

        private void MainForm_Activated(object sender, EventArgs e)
        {
            //LevelSelectForm f = new LevelSelectForm();
            //f.ShowDialog(this);
        }

        private void ui_pbImage_MouseDown(object sender, MouseEventArgs e)
        {
            PictureBox pb = sender as PictureBox;

            if (pb == null)
                return;

            if (e.Button == MouseButtons.Left)
            {
                pb.Image = null;
            }
            else if (e.Button == MouseButtons.Right)
            {
                pb.Image = Image.FromFile("image.png");
            }
            
        }
    }
}
