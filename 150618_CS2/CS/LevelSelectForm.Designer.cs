namespace CS
{
    partial class LevelSelectForm
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
            this.ui_rb1 = new System.Windows.Forms.RadioButton();
            this.ui_rb2 = new System.Windows.Forms.RadioButton();
            this.ui_rb3 = new System.Windows.Forms.RadioButton();
            this.ui_btnConfirm = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // ui_rb1
            // 
            this.ui_rb1.AutoSize = true;
            this.ui_rb1.Location = new System.Drawing.Point(13, 13);
            this.ui_rb1.Name = "ui_rb1";
            this.ui_rb1.Size = new System.Drawing.Size(47, 16);
            this.ui_rb1.TabIndex = 0;
            this.ui_rb1.TabStop = true;
            this.ui_rb1.Text = "초급";
            this.ui_rb1.UseVisualStyleBackColor = true;
            // 
            // ui_rb2
            // 
            this.ui_rb2.AutoSize = true;
            this.ui_rb2.Location = new System.Drawing.Point(13, 35);
            this.ui_rb2.Name = "ui_rb2";
            this.ui_rb2.Size = new System.Drawing.Size(47, 16);
            this.ui_rb2.TabIndex = 1;
            this.ui_rb2.TabStop = true;
            this.ui_rb2.Text = "중급";
            this.ui_rb2.UseVisualStyleBackColor = true;
            // 
            // ui_rb3
            // 
            this.ui_rb3.AutoSize = true;
            this.ui_rb3.Location = new System.Drawing.Point(13, 57);
            this.ui_rb3.Name = "ui_rb3";
            this.ui_rb3.Size = new System.Drawing.Size(47, 16);
            this.ui_rb3.TabIndex = 2;
            this.ui_rb3.TabStop = true;
            this.ui_rb3.Text = "고급";
            this.ui_rb3.UseVisualStyleBackColor = true;
            // 
            // ui_btnConfirm
            // 
            this.ui_btnConfirm.Location = new System.Drawing.Point(13, 91);
            this.ui_btnConfirm.Name = "ui_btnConfirm";
            this.ui_btnConfirm.Size = new System.Drawing.Size(75, 23);
            this.ui_btnConfirm.TabIndex = 3;
            this.ui_btnConfirm.Text = "확인";
            this.ui_btnConfirm.UseVisualStyleBackColor = true;
            this.ui_btnConfirm.Click += new System.EventHandler(this.ui_btnConfirm_Click);
            // 
            // LevelSelectForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(176, 141);
            this.Controls.Add(this.ui_btnConfirm);
            this.Controls.Add(this.ui_rb3);
            this.Controls.Add(this.ui_rb2);
            this.Controls.Add(this.ui_rb1);
            this.Name = "LevelSelectForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "난이도";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton ui_rb1;
        private System.Windows.Forms.RadioButton ui_rb2;
        private System.Windows.Forms.RadioButton ui_rb3;
        private System.Windows.Forms.Button ui_btnConfirm;
    }
}