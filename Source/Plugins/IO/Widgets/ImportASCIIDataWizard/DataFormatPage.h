/* ============================================================================
* Copyright (c) 2009-2016 BlueQuartz Software, LLC
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice, this
* list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
* contributors may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


#ifndef _dataformatpage_h_
#define _dataformatpage_h_

#include <QtWidgets/QWizardPage>

#include "SIMPLib/DataContainers/DataContainerArray.h"

#include "AbstractWizardPage.h"

#include "ui_DataFormatPage.h"

class ASCIIDataModel;
class EditHeadersDialog;
class QSignalMapper;
class QtSFaderWidget;

class DataFormatPage : public AbstractWizardPage, private Ui::DataFormatPage
{
  Q_OBJECT

  public:
    /**
    * @brief Constructor
    * @param parameter The FilterParameter object that this widget represents
    * @param filter The instance of the filter that this parameter is a part of
    * @param parent The parent QWidget for this Widget
    */
    DataFormatPage(const QString &inputFilePath, int numLines, DataContainerArray::Pointer dca, QWidget* parent = NULL);

    virtual ~DataFormatPage();

    /**
     * @brief Initializes some of the GUI elements with selections or other GUI related items
     */
    virtual void setupGui();

    /**
    * @brief Refreshes the model
    */
    virtual void refreshModel();

    /**
    * @brief Launches the "Edit Headers" dialog
    */
    void launchEditHeadersDialog();

    /**
     * @brief checkHeaders
     * @param headers
     */
    void checkHeaders(QVector<QString> headers);

    /**
    * @brief Controls which page to navigate to after the user clicks "Next" button
    */
    virtual int nextId() const;

    /**
    * @brief Resets the page when the user hits the "Back" button
    */
    virtual void cleanupPage();

    /**
     * @brief isComplete
     * @return
     */
    bool isComplete() const;

    /**
     * @brief getTupleTable
     * @return
     */
    TupleTableWidget* getTupleTable();

    /**
     * @brief getAutomaticAM
     * @return
     */
    bool getAutomaticAM();

    /**
     * @brief getSelectedPath
     * @return
     */
    DataArrayPath getSelectedPath();

    /**
     * @brief getAMName
     * @return
     */
    QString getAMName();

    /**
     * @brief eventFilter
     * @param obj
     * @param event
     * @return
     */
    bool eventFilter(QObject* obj, QEvent* event);

  public slots:
    /**
     * @brief dcaItemSelected
     * @param path
     */
    void amItemSelected(QString path);

    /**
     * @brief dcaItemSelected
     * @param path
     */
    void dcItemSelected(QString path);

    /**
     * @brief on_amName_returnPressed
     */
//    void on_amName_returnPressed();

    /**
     * @brief on_applyChangesBtn_clicked
     */
    void on_applyChangesBtn_clicked();

    /**
     * @brief hideButton
     */
    void hideButton();

    /**
     * @brief widgetChanged
     * @param msg
     */
    void widgetChanged(const QString& msg);

  protected:
    /**
     * @brief showEvent
     * @param event
     */
    void showEvent(QShowEvent* event);

    /**
     * @brief adjustedMenuPosition
     * @param pushButton
     * @return
     */
    QPoint adjustedMenuPosition(QPushButton* pushButton);

  protected slots:
    void on_startRowSpin_valueChanged(int i);
    void on_hasHeadersRadio_toggled(bool checked);
    void on_amAutomatically_stateChanged(int state);
    void on_selectedAMBtn_pressed();
    void on_selectedDCBtn_pressed();
    void on_headersIndexLineEdit_textChanged(const QString &text);
    void on_editHeadersBtn_clicked();
    void on_dataTypeRadio_clicked();
    void on_skipRadio_clicked();
    void on_dataTypeCB_currentTextChanged(const QString &text);

    void updateSelection(const QItemSelection &selected, const QItemSelection &deselected);
    bool checkTupleDimensions(QVector<size_t> tupleDims) const;

  private:
    int                                             m_NumLines;
    EditHeadersDialog*                              m_EditHeadersDialog;
    DataContainerArray::Pointer                     m_Dca;

    QSignalMapper*                                  m_AMMenuMapper;
    QSignalMapper*                                  m_DCMenuMapper;

    QPointer<QtSFaderWidget>                        m_FaderWidget;

    bool validateHeaders(QVector<QString> headers);
    bool validateTupleDimensions(QVector<size_t> tupleDims) const;

    DataFormatPage(const DataFormatPage&); // Copy Constructor Not Implemented
    void operator=(const DataFormatPage&); // Operator '=' Not Implemented
};

#endif /* DataFormatPage_H_ */
