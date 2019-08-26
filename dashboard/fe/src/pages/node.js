import React from 'react';
import { connect } from 'react-redux';
import { PageHeader } from 'antd';

class Page extends React.PureComponent {

    render() {
        return (
            <div>
                <PageHeader title="主机资产" />
            </div>
        );
    }
}

export default connect()(Page);
