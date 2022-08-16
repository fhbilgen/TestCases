namespace ManagedTest
{
    partial class frmMemoryTests
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
            this.gbObjType = new System.Windows.Forms.GroupBox();
            this.lblNumOfObjectsToAdd = new System.Windows.Forms.Label();
            this.lblNumOfObjectsToRemove = new System.Windows.Forms.Label();
            this.txtAdd = new System.Windows.Forms.TextBox();
            this.txtRemove = new System.Windows.Forms.TextBox();
            this.btnAdd = new System.Windows.Forms.Button();
            this.btnRemove = new System.Windows.Forms.Button();
            this.rbManaged = new System.Windows.Forms.RadioButton();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.btnGCCollect = new System.Windows.Forms.Button();
            this.lblNumOfObjects = new System.Windows.Forms.Label();
            this.txtNumOfObj = new System.Windows.Forms.TextBox();
            this.gbObjType.SuspendLayout();
            this.SuspendLayout();
            // 
            // gbObjType
            // 
            this.gbObjType.Controls.Add(this.radioButton1);
            this.gbObjType.Controls.Add(this.rbManaged);
            this.gbObjType.Location = new System.Drawing.Point(12, 23);
            this.gbObjType.Name = "gbObjType";
            this.gbObjType.Size = new System.Drawing.Size(547, 112);
            this.gbObjType.TabIndex = 0;
            this.gbObjType.TabStop = false;
            this.gbObjType.Text = "Object Type";
            // 
            // lblNumOfObjectsToAdd
            // 
            this.lblNumOfObjectsToAdd.AutoSize = true;
            this.lblNumOfObjectsToAdd.Location = new System.Drawing.Point(23, 192);
            this.lblNumOfObjectsToAdd.Name = "lblNumOfObjectsToAdd";
            this.lblNumOfObjectsToAdd.Size = new System.Drawing.Size(276, 25);
            this.lblNumOfObjectsToAdd.TabIndex = 1;
            this.lblNumOfObjectsToAdd.Text = "Number of Objects to Add : ";
            // 
            // lblNumOfObjectsToRemove
            // 
            this.lblNumOfObjectsToRemove.AutoSize = true;
            this.lblNumOfObjectsToRemove.Location = new System.Drawing.Point(23, 262);
            this.lblNumOfObjectsToRemove.Name = "lblNumOfObjectsToRemove";
            this.lblNumOfObjectsToRemove.Size = new System.Drawing.Size(317, 25);
            this.lblNumOfObjectsToRemove.TabIndex = 2;
            this.lblNumOfObjectsToRemove.Text = "Number of Objects to Remove : ";
            // 
            // txtAdd
            // 
            this.txtAdd.Location = new System.Drawing.Point(386, 186);
            this.txtAdd.Name = "txtAdd";
            this.txtAdd.Size = new System.Drawing.Size(173, 31);
            this.txtAdd.TabIndex = 3;
            // 
            // txtRemove
            // 
            this.txtRemove.Location = new System.Drawing.Point(386, 259);
            this.txtRemove.Name = "txtRemove";
            this.txtRemove.Size = new System.Drawing.Size(173, 31);
            this.txtRemove.TabIndex = 4;
            // 
            // btnAdd
            // 
            this.btnAdd.Location = new System.Drawing.Point(644, 175);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(132, 52);
            this.btnAdd.TabIndex = 5;
            this.btnAdd.Text = "Add";
            this.btnAdd.UseVisualStyleBackColor = true;
            this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
            // 
            // btnRemove
            // 
            this.btnRemove.Location = new System.Drawing.Point(644, 248);
            this.btnRemove.Name = "btnRemove";
            this.btnRemove.Size = new System.Drawing.Size(132, 52);
            this.btnRemove.TabIndex = 6;
            this.btnRemove.Text = "Remove";
            this.btnRemove.UseVisualStyleBackColor = true;
            this.btnRemove.Click += new System.EventHandler(this.btnRemove_Click);
            // 
            // rbManaged
            // 
            this.rbManaged.AutoSize = true;
            this.rbManaged.Location = new System.Drawing.Point(16, 45);
            this.rbManaged.Name = "rbManaged";
            this.rbManaged.Size = new System.Drawing.Size(201, 29);
            this.rbManaged.TabIndex = 0;
            this.rbManaged.TabStop = true;
            this.rbManaged.Text = "Managed Object";
            this.rbManaged.UseVisualStyleBackColor = true;
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Location = new System.Drawing.Point(267, 45);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(172, 29);
            this.radioButton1.TabIndex = 1;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "Native Object";
            this.radioButton1.UseVisualStyleBackColor = true;
            // 
            // btnGCCollect
            // 
            this.btnGCCollect.Location = new System.Drawing.Point(627, 370);
            this.btnGCCollect.Name = "btnGCCollect";
            this.btnGCCollect.Size = new System.Drawing.Size(149, 52);
            this.btnGCCollect.TabIndex = 7;
            this.btnGCCollect.Text = "GC Collect !";
            this.btnGCCollect.UseVisualStyleBackColor = true;
            this.btnGCCollect.Click += new System.EventHandler(this.btnGCCollect_Click);
            // 
            // lblNumOfObjects
            // 
            this.lblNumOfObjects.AutoSize = true;
            this.lblNumOfObjects.Location = new System.Drawing.Point(28, 338);
            this.lblNumOfObjects.Name = "lblNumOfObjects";
            this.lblNumOfObjects.Size = new System.Drawing.Size(255, 25);
            this.lblNumOfObjects.TabIndex = 8;
            this.lblNumOfObjects.Text = "Number of Objects Active";
            // 
            // txtNumOfObj
            // 
            this.txtNumOfObj.Location = new System.Drawing.Point(289, 338);
            this.txtNumOfObj.Name = "txtNumOfObj";
            this.txtNumOfObj.Size = new System.Drawing.Size(173, 31);
            this.txtNumOfObj.TabIndex = 9;
            // 
            // frmMemoryTests
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(805, 465);
            this.Controls.Add(this.txtNumOfObj);
            this.Controls.Add(this.lblNumOfObjects);
            this.Controls.Add(this.btnGCCollect);
            this.Controls.Add(this.btnRemove);
            this.Controls.Add(this.btnAdd);
            this.Controls.Add(this.txtRemove);
            this.Controls.Add(this.txtAdd);
            this.Controls.Add(this.lblNumOfObjectsToRemove);
            this.Controls.Add(this.lblNumOfObjectsToAdd);
            this.Controls.Add(this.gbObjType);
            this.Name = "frmMemoryTests";
            this.Text = "Memory Tests";
            this.gbObjType.ResumeLayout(false);
            this.gbObjType.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox gbObjType;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.RadioButton rbManaged;
        private System.Windows.Forms.Label lblNumOfObjectsToAdd;
        private System.Windows.Forms.Label lblNumOfObjectsToRemove;
        private System.Windows.Forms.TextBox txtAdd;
        private System.Windows.Forms.TextBox txtRemove;
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.Button btnRemove;
        private System.Windows.Forms.Button btnGCCollect;
        private System.Windows.Forms.Label lblNumOfObjects;
        private System.Windows.Forms.TextBox txtNumOfObj;
    }
}