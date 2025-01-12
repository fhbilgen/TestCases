namespace ManagedTest
{
    partial class frmMain
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.memoryToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.testsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.jITToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.jSONSerializeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exceptionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nativeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.managedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.memoryToolStripMenuItem,
            this.jITToolStripMenuItem,
            this.exceptionToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(4, 1, 0, 1);
            this.menuStrip1.Size = new System.Drawing.Size(549, 26);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // memoryToolStripMenuItem
            // 
            this.memoryToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.testsToolStripMenuItem});
            this.memoryToolStripMenuItem.Name = "memoryToolStripMenuItem";
            this.memoryToolStripMenuItem.Size = new System.Drawing.Size(78, 24);
            this.memoryToolStripMenuItem.Text = "Memory";
            // 
            // testsToolStripMenuItem
            // 
            this.testsToolStripMenuItem.Name = "testsToolStripMenuItem";
            this.testsToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.testsToolStripMenuItem.Text = "Tests";
            this.testsToolStripMenuItem.Click += new System.EventHandler(this.testsToolStripMenuItem_Click);
            // 
            // jITToolStripMenuItem
            // 
            this.jITToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.jSONSerializeToolStripMenuItem});
            this.jITToolStripMenuItem.Name = "jITToolStripMenuItem";
            this.jITToolStripMenuItem.Size = new System.Drawing.Size(40, 24);
            this.jITToolStripMenuItem.Text = "JIT";
            // 
            // jSONSerializeToolStripMenuItem
            // 
            this.jSONSerializeToolStripMenuItem.Name = "jSONSerializeToolStripMenuItem";
            this.jSONSerializeToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.jSONSerializeToolStripMenuItem.Text = "JSON Serialize";
            // 
            // exceptionToolStripMenuItem
            // 
            this.exceptionToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.nativeToolStripMenuItem,
            this.managedToolStripMenuItem});
            this.exceptionToolStripMenuItem.Name = "exceptionToolStripMenuItem";
            this.exceptionToolStripMenuItem.Size = new System.Drawing.Size(88, 24);
            this.exceptionToolStripMenuItem.Text = "Exception";
            // 
            // nativeToolStripMenuItem
            // 
            this.nativeToolStripMenuItem.Name = "nativeToolStripMenuItem";
            this.nativeToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.nativeToolStripMenuItem.Text = "Native";
            this.nativeToolStripMenuItem.Click += new System.EventHandler(this.nativeToolStripMenuItem_Click);
            // 
            // managedToolStripMenuItem
            // 
            this.managedToolStripMenuItem.Name = "managedToolStripMenuItem";
            this.managedToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.managedToolStripMenuItem.Text = "Managed";
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(549, 341);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "frmMain";
            this.Text = "Managed Test Console";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem memoryToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem testsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem jITToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem jSONSerializeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exceptionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nativeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem managedToolStripMenuItem;
    }
}

