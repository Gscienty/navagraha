import React from 'react';
import { connect } from 'react-redux';
import { PageHeader } from 'antd';

class Page extends React.PureComponent {

    constructor(props) {
        super(props);
    }

    render() {
        return (
            <div>
                <PageHeader title="函数服务" />
            </div>
        );
    }
}

export default connect()(Page);
