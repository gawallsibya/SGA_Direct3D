using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CS
{
    public partial class LevelSelectForm : Form
    {
        public LevelSelectForm()
        {
            InitializeComponent();
        }

        private void ui_btnConfirm_Click(object sender, EventArgs e)
        {
            foreach (Control c in this.Controls)
            {
                RadioButton rb = c as RadioButton;
                if (rb == null) continue;

                if (rb.Checked)
                {
                    MainForm f = this.Owner as MainForm;
                    if (f != null)
                    {
                        f.SetLevel(1);
                    }
                }
            }
        }
    }
}
