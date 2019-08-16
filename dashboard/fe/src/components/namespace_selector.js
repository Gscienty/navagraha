import React from 'react';
import { Select } from 'antd';
import { connect } from 'react-redux';
import {
    NAMESPACE_LIST_UNSET,
    NAMESPACE_LIST_SET,
    fetchNamespaces,
    selectDisplayNamespace
} from '../actions/namespace';

const { Option } = Select;

class NamespaceSelector extends React.PureComponent {

    constructor(props) {
        super(props);

        if (this.props.namespace.state === NAMESPACE_LIST_UNSET) {
            this.props.dispatch(fetchNamespaces());
        }
    }

    render() {
        if (this.props.namespace.state === NAMESPACE_LIST_SET) {
            return (
                <div>
                    <Select
                        value={this.props.namespace.selectedNamespace}
                        showArrow={false}
                        size="large"
                        style={{
                            border: 'none'
                        }}
                        onSelect={value => this.props.dispatch(selectDisplayNamespace(value))}>
                    {(() => {
                        return this.props.namespace.namespace
                        .map(n => <Option key={`${n.name}`} value={`${n.name}`}>{n.name}</Option>)
                    })()}
                    </Select>
                </div>
            );
        }
        else {
            return (
                <div>
                </div>
            );
        }
    }
};


export default connect(({ namespace }) => ({
    namespace
}))(NamespaceSelector);

