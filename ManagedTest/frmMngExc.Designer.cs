namespace ManagedTest
{
    partial class frmMngExc
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
            this.btnExc = new System.Windows.Forms.Button();
            this.btnExcHnd = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnExc
            // 
            this.btnExc.Location = new System.Drawing.Point(99, 42);
            this.btnExc.Name = "btnExc";
            this.btnExc.Size = new System.Drawing.Size(196, 23);
            this.btnExc.TabIndex = 0;
            this.btnExc.Text = "Throw exception";
            this.btnExc.UseVisualStyleBackColor = true;
            this.btnExc.Click += new System.EventHandler(this.btnExc_Click);
            // 
            // btnExcHnd
            // 
            this.btnExcHnd.Location = new System.Drawing.Point(99, 89);
            this.btnExcHnd.Name = "btnExcHnd";
            this.btnExcHnd.Size = new System.Drawing.Size(196, 23);
            this.btnExcHnd.TabIndex = 1;
            this.btnExcHnd.Text = "Throw exception and handle";
            this.btnExcHnd.UseVisualStyleBackColor = true;
            this.btnExcHnd.Click += new System.EventHandler(this.btnExcHnd_Click);
            // 
            // frmMngExc
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.btnExcHnd);
            this.Controls.Add(this.btnExc);
            this.Name = "frmMngExc";
            this.Text = "frmMngExc";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnExc;
        private System.Windows.Forms.Button btnExcHnd;
    }
}