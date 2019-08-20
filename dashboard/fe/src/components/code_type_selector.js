import React from 'react';
import { connect } from 'react-redux';
import { Select } from 'antd';
import {
    fetchCodeTemplate,
    fetchCodeTemplateList,
    CODE_TEMPLATE_LIST_UNSET
} from '../actions/code';
const { Option } = Select;

class CodeTypeSelector extends React.Component {

    constructor(props) {
        super(props);

        if (this.props.state === CODE_TEMPLATE_LIST_UNSET) {
            this.props.dispatch(fetchCodeTemplateList());
        }
    }

    render() {
        return (
            <Select
                value={this.props.selectedType}
                size="large"
                onSelect={n => this.props.dispatch(fetchCodeTemplate(n))}>
                {(() => (
                    this.props.types.map(n => <Option key={`${n}`} value={`${n}`}>{n}</Option>)
                ))()}
            </Select>
        )
    }
};

export default connect(({ code }) => ({
    types: code.templateType,
    state: code.templateTypeState,
    selectedType: code.selectedTemplateType
}))(CodeTypeSelector);
