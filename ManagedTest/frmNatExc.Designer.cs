namespace ManagedTest
{
    partial class frmNatExc
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
            this.btnAV = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnAV
            // 
            this.btnAV.Location = new System.Drawing.Point(59, 35);
            this.btnAV.Name = "btnAV";
            this.btnAV.Size = new System.Drawing.Size(75, 23);
            this.btnAV.TabIndex = 0;
            this.btnAV.Text = "AV";
            this.btnAV.UseVisualStyleBackColor = true;
            this.btnAV.Click += new System.EventHandler(this.btnAV_Click);
            // 
            // frmNatExc
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.btnAV);
            this.Name = "frmNatExc";
            this.Text = "frmNatExc";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnAV;
    }
}